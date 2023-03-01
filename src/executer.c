#include "../inc/minishell.h"

/* function changes the filedescriptors always
 * 		- from stdin to 'infile' in 'parsed_chunk'
 *		- and from stdout to 'outfile' in 'parsed_chunk' */
void redirection(t_parsed_chunk *parsed_node)
{
	dup2(parsed_node->infile, STDIN_FILENO);
	dup2(parsed_node->outfile, STDOUT_FILENO);
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
		close(parsed_list->pipe_fds[0]);
		close(parsed_list->pipe_fds[1]);
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
	while (pipegroups > 0)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			// redirection (dup2())
			redirection(parsed_node);

			// close filediscriptors (pipes and files)
			close_fds(parsed_node, pipegroups);
			// execute command
			execute_cmd(parsed_node, ori_env);
		}
		pipegroups--;
	}
	// loop where we wait for kiddos to finish
}