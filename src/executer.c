#include "../inc/minishell.h"

/* function changes the filedescriptors always
 * 		- from stdin to 'infile' in 'parsed_chunk'
 *		- and from stdout to 'outfile' in 'parsed_chunk' */
void redirection(t_parsed_chunk *parsed_node, int32_t i, int32_t pipegroups, int32_t pipe_fds[MAX_FD][2])
{
	write(2, RED"\nls | wc case:\n"RESET, 20);
	write(2, "infile: ", 8);
	write(2, ft_itoa(parsed_node->infile), 2);
	write(2, "\n", 1);
	write(2, "outfile: ", 9);
	write(2, ft_itoa(parsed_node->outfile), 2);
	write(2, "\n", 1);
	// printf("file id: %d\n", parsed_node->outfile);
	// printf("pipegroups: %d\ni: %d\n", pipegroups, i);
	write(2, "\nREDIRECTION:\n", 14);
	if (i == 0)
	{
		write(2, "start of pipegroup\n", 19);
		if (parsed_node->infile != 0)
		{
			write(2, "input: infile-\n", 15);
			dup2(parsed_node->infile, STDIN_FILENO);
		}
		else
			write(2, "input: STDIN-\n", 14);

		// there is another pipegroup afterwards
		if (pipegroups > i+1)
		{
			if (parsed_node->outfile != 1)
			{
				write(2, "uhm outfile before pipe, duh? (how to handle redir?) | EXIT\n", 60);
				exit(0);
			}
			write(2, "output: PIPE[1]-\n", 17);
			dup2(pipe_fds[i][1], STDOUT_FILENO);
		}
		else
		{
			if (parsed_node->outfile != 1)
			{
				write(2, "output: outfile-\n", 17);
				dup2(parsed_node->outfile, STDOUT_FILENO);
			}
			else
			write(2, "output: STDOUT-\n", 16);
		}
	} // end of pipegroups
	else if ((i+1) == pipegroups)
	{	// reading from last pipe
		write(2, "end of pipegroup\n", 17);
		dup2(pipe_fds[i-1][0], STDIN_FILENO);
		write(2, "input: PIPE[0]-\n", 16);

		if (parsed_node->outfile != 1)
		{
			write(2, "output: outfile-\n", 17);
			dup2(parsed_node->outfile, STDOUT_FILENO);
		}
		else
			write(2, "output: STDOUT-\n", 16);

	}
	else // in the middle of pipegroups
	{
			write(2, "input: PIPE[0]-\n", 16);
			dup2(pipe_fds[i][0], parsed_node->infile);
			write(2, "output: PIPE[1]-\n", 17);
			dup2(pipe_fds[i][1], parsed_node->outfile);
		// write(2, "middle of pipegroup\n", 20);
		// if (parsed_node->infile != 0)
		// {
		// 	write(2, "input: PIPE[0]-\n", 16);
		// 	dup2(pipe_fds[i-1][0], STDIN_FILENO);
		// }
		// else
		// 	write(2, "input: STDIN\n", 13);
		// if (parsed_node->outfile != 1)
		// {
		// 	write(2, "output: PIPE[1]-\n", 17);
		// 	dup2(pipe_fds[i][1], STDOUT_FILENO);
		// }
		// else
		// 	write(2, "output: STDOU\n", 14);
	}
// write(2, "REDIRECTION DONE-\n\n", 19);

}

void open_pipefds(t_hold *hold, int32_t pipegroups, int32_t pipe_fds[MAX_FD][2])
{
	int32_t i;

	i = 0;
	while (i + 1 < pipegroups)
	{
		if (pipe(pipe_fds[i]) < 0)
		{
			// set error code
			exit_status(hold, "Error! Failed to open pipe!\n", 69);
			exit(0);
		}
		
		i++;
	}
	printf(MAG"opend %d pipes\n"RESET, i);
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
	printf("\n%s\n\n", parsed_node->args[0]);
	if (builtin_parser(parsed_node->args[0]) == true)
	{
		printf(CYN"my builtin:\n"RESET);
		builtin(hold, parsed_node);
	}
	else if (execve(parsed_node->cmd_path, parsed_node->args, ori_env) == -1)
	{
		write(2, "Command not found: ", 19);

		// not sure when to print all commands that failing
		int32_t i = 0;
		// while (parsed_node->args[i] != NULL)
		// {
			write(2, parsed_node->args[i], ft_strlen(parsed_node->args[i]));
		// 	i++;
		// }
		write(2, "\n", 1);

		// using exit here?
		// exit(127);
	}
	// free(path);
}

void executer(t_hold *hold, char **ori_env)
{
	// printf("in executer\n");
	int32_t *pids;
	int32_t pipegroups;
	int32_t	i;
	t_parsed_chunk *parsed_node;
	int32_t pipe_fds[MAX_FD][2];

	parsed_node = hold->parsed_list;
	// write(2, GRN"check\n"RESET, 11);
	if (hold->exit_code != 0)
	{
		printf("exit_code: %d\n", hold->exit_code);
		return ;
	}
	// print_parsed_list(hold->parsed_list);

	pipegroups = count_pipegroups(hold->lex_struct);

	// malloc array with process-id's for forking:
	pids = malloc(sizeof(int32_t) * pipegroups);
	if (!pids)
		return (exit_status(hold, "Error! Failed to malloc for pids (in executer())\n", 69));

	// open amount of pipes we need (one pipegroup = one pipe)
	open_pipefds(hold, pipegroups, pipe_fds);

	i = 0;
	printf("\npipegroups: %d\n", pipegroups);
	while (i < pipegroups)
	{
		// write(2, GRN"eEEEEeeeEEEEEe\n"RESET, 15);
		pids[i] = fork();
		if (pids[i] == 0)
		{
			redirection(parsed_node, i, pipegroups, pipe_fds);

			// close filediscriptors (pipes and files)
			close_fds(parsed_node, pipegroups, pipe_fds);

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
			// close_fds(parsed_node, pipegroups, pipe_fds);
			// waitpid(pids[i], NULL, 0);
		}
		// waitpid(pids[i], NULL, 0);
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
