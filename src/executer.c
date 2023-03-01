#include "../inc/minishell.h"

/* function changes the filedescriptors always
 * 		- from stdin to 'infile' in 'parsed_chunk'
 *		- and from stdout to 'outfile' in 'parsed_chunk' */
void redirection(t_parsed_chunk *parsed_node, int32_t i, int32_t pipegroups)
{
	printf("file id: %d\n", parsed_node->outfile);
	printf("pipegroups: %d\ni: %d\n", pipegroups, i);
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
			dup2(parsed_node->pipe_fds[i][1], STDOUT_FILENO);
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
		write(2, "i: ", 3);
		// char *brr = ;
		write(2, ft_itoa(i), 1);
		write(2, "\n", 1);
		dup2(parsed_node->pipe_fds[i-1][0], STDIN_FILENO);
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
		write(2, "middle of pipegroup\n", 20);
		if (parsed_node->infile != 0)
		{
			write(2, "input: PIPE[0]-\n", 16);
			dup2(parsed_node->pipe_fds[i][0], STDIN_FILENO);
		}
		if (parsed_node->outfile != 1)
		{
			write(2, "output: PIPE[1]-\n", 17);
			dup2(parsed_node->pipe_fds[i][1], STDOUT_FILENO);
		}
	}
write(2, "REDIRECTION DONE-\n\n", 19);

}

void open_pipefds(t_parsed_chunk *parsed_list, int32_t pipegroups)
{
	int32_t i;

	i = 1;
	while (i < pipegroups)
	{
		if (pipe(parsed_list->pipe_fds[i]) < 0)
		{
			// set error code
			write(2, "Failed to malloc for pipe! EXIT\n", 35);
			exit(0);
		}
		i++;
	}
	printf("opend %d pipes\n", i-1);
}

void close_fds(t_parsed_chunk *parsed_list, int32_t pipegroups)
{
	int32_t i;
	t_parsed_chunk *tmp;

	i = 1;
	tmp = parsed_list;
	while (i < pipegroups)
	{
		close(parsed_list->pipe_fds[i][0]);
		close(parsed_list->pipe_fds[i][1]);
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

void execute_cmd(t_parsed_chunk *parsed_node, char **ori_env)
{
	if (execve(parsed_node->cmd_path, parsed_node->args, ori_env) == -1)
	{
		write(2, "Command not found: ", 19);
		// ft_putstr_fd(ppx->av[3], 2);
		exit(127);
	}
	// free(path);
}

void executer(t_hold *hold, char **ori_env)
{
	int32_t *pids;
	int32_t pipegroups;
	int32_t	i;
	t_parsed_chunk *parsed_node;

	parsed_node = hold->parsed_list;
	if (hold->exit_code != 0)
		return ;
	// print_parsed_list(hold->parsed_list);

	pipegroups = count_pipegroups(hold->lex_struct);

	// malloc array with process-id's for forking:
	pids = malloc(sizeof(int32_t) * pipegroups);
	if (!pids)
		return (exit_status(hold, "Error! Failed to malloc for pids (in executer())\n", 69));

	// open amount of pipes we need (one pipegroup = one pipe)
	open_pipefds(hold->parsed_list, pipegroups);

	i = 0;
	while (i < pipegroups)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			// redirection (dup2())
			redirection(parsed_node, i, pipegroups);

			// close filediscriptors (pipes and files)
			close_fds(parsed_node, pipegroups);
			// execute command
			execute_cmd(parsed_node, ori_env);
		}
		i++;
	}
		waitpid(-1, NULL, 0);
	// loop where we wait for kiddos to finish
}