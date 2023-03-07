#include "../inc/minishell.h"

/* function changes the filedescriptors always
 * 		- from stdin to 'infile' in 'parsed_chunk'
 *		- and from stdout to 'outfile' in 'parsed_chunk' */
void redirection(t_parsed_chunk *parsed_node, int32_t i, int32_t pipegroups, int32_t pipe_fds[MAX_FD][2])
{
	if (i == 0)
	{
		if (parsed_node->infile != 0)
			dup2(parsed_node->infile, STDIN_FILENO);
		if (pipegroups > i+1) // there is another pipegroup afterwards
		{
			if (parsed_node->outfile != 1)
			{
				write(2, "uhm outfile before pipe, duh? (how to handle redir?) | EXIT\n", 60);
				exit(0);
			}
			dup2(pipe_fds[i][1], STDOUT_FILENO);
		}
		else
		{
			if (parsed_node->outfile != 1)
				dup2(parsed_node->outfile, STDOUT_FILENO);
		}
	}
	else if ((i+1) == pipegroups) // end of pipegroups
	{
		dup2(pipe_fds[i-1][0], STDIN_FILENO);
		if (parsed_node->outfile != 1)
			dup2(parsed_node->outfile, STDOUT_FILENO);
	}
	else // in the middle of pipegroups
	{
		dup2(pipe_fds[i][0], parsed_node->infile);
		dup2(pipe_fds[i][1], parsed_node->outfile);
	}
}

void open_pipefds(t_hold *hold, int32_t pipegroups, int32_t pipe_fds[MAX_FD][2])
{
	int32_t i;

	i = 0;
	while (i + 1 < pipegroups)
	{
		if (pipe(pipe_fds[i]) < 0)
		{
			exit_status(hold, "Error! Failed to open pipe!\n", 69);
			exit(0);
		}
		
		i++;
	}
}

void close_fds(t_parsed_chunk *parsed_list, int32_t pipegroups, int32_t pipe_fds[MAX_FD][2])
{
	int32_t i;
	t_parsed_chunk *tmp;

	i = 0;
	tmp = parsed_list;
	while ((i+1) < pipegroups)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		i++;
	}
	while (tmp != NULL)
	{
		if (parsed_list->infile != 0)
			close(parsed_list->infile);
		if (parsed_list->outfile != 1)
			close(parsed_list->outfile);
		tmp = tmp->next;
	}
}

void execute_cmd(t_hold *hold, t_parsed_chunk *parsed_node, char **ori_env)
{
	// if (builtin_parser(parsed_node->args[0]) == true)
	// {
	// 	write(2, CYN"BUILTIN\n", 15);
	// 	builtin(hold, parsed_node);
	// 	exit(69);
	// }
	// else 
	if (execve(parsed_node->cmd_path, parsed_node->args, ori_env) == -1)
	{
		write(2, RED"minihell: ", 16);
		write(2, parsed_node->args[0], ft_strlen(parsed_node->args[0]));
		exit_status(hold, RED": command not found!\n"RESET, 69);
		exit(127);
	}
}

void executer(t_hold *hold, char **ori_env)
{
	int32_t *pids;
	int32_t pipegroups;
	int32_t	i;
	t_parsed_chunk *parsed_node;
	int32_t pipe_fds[MAX_FD][2];

	parsed_node = hold->parsed_list;
	if (hold->exit_code != 0)
		return ;
	pipegroups = count_pipegroups(hold->lex_struct);
	pids = malloc(sizeof(int32_t) * pipegroups);
	if (!pids)
		return (exit_status(hold, MAG"Error! Failed to malloc for pids (in executer())\n"RESET, 69));
	open_pipefds(hold, pipegroups, pipe_fds);
	i = 0;
	while (i < pipegroups)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			redirection(parsed_node, i, pipegroups, pipe_fds);

			// close filediscriptors (pipes and files)
			close_fds(parsed_node, pipegroups, pipe_fds);
			if (builtin_parser(parsed_node->args[0]) == true)
			{
				write(2, CYN"BUILTIN\n", 15);
				builtin(hold, parsed_node);
			}
			else
				execute_cmd(hold, parsed_node, ori_env);
		}
		else
		{
			close(pipe_fds[i][1]);
			if (i != 0)
				close(pipe_fds[i-1][0]);
			// close(pipe_fds[i][0]);
			if (parsed_node->infile != 0)
				close(parsed_node->infile);
			if (parsed_node->outfile != 1)
				close(parsed_node->outfile);
		}
		i++;
		parsed_node = parsed_node->next;
	}
	close(pipe_fds[i-1][0]); // not sure which 
	close(pipe_fds[i][0]); // one of these two

	// loop where we wait for kiddos to finish
	i=0;
	while ((i < pipegroups) && (pids[i]))
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
	free(pids);
}
