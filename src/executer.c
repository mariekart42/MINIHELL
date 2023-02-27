#include "../inc/minishell.h"

/* function changes the filedescriptors always
 * 		- from stdin to 'infile' in 'parsed_chunk'
 *		- and from stdout to 'outfile' in 'parsed_chunk' */
void redirection(t_parsed_chunk *parsed_node)
{
	dup2(parsed_node->infile, STDIN_FILENO);
	dup2(parsed_node->outfile, STDOUT_FILENO);
}

void open_pipefds(t_hold *hold, int32_t pipe_groups)
{
	int32_t i;
	i = 0;
	while (i < pipe_groups)
	{
		if (pipe(hold->parsed_list->pipe_fds[i]) < 0)
			exit_status(hold, "Error! Failed to open pipe fd's in open_pipefds()!\n", 69);
		i++;
	}
}

void close_fds(t_parsed_chunk *parsed_node)
{
	parsed_node->pipe_fds[0][0] = 69;
	printf("%d\n", parsed_node->pipe_fds[0][0]);

}

void executer(t_hold *hold)
{
	printf("in executer\n");
	int32_t *pids;
	int32_t pipegroups;
	int32_t	i;
	t_parsed_chunk *parsed_node;
	// int32_t pipe_fds[MAX_FD][2];

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
	open_pipefds(hold, pipegroups);

	i = 0;
	while (pipegroups > 0)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			// redirection (dup2())
			redirection(parsed_node);

			// close filediscriptors (pipes and files)
			close_fds(parsed_node);

			// execute command

		}


		pipegroups--;
	}
	// loop where we wait for kiddos to finish
}