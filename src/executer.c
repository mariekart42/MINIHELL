#include "../inc/minishell.h"

/* function changes the filedescriptors always
 * 		- from stdin to 'infile' in 'parsed_chunk'
 *		- and from stdout to 'outfile' in 'parsed_chunk' */
void redirection(t_parsed_chunk *parsed_node, int32_t i, int32_t pipegroups, int32_t pipe_fds[MAX_FD][2])
{
	dup2(parsed_node->infile, STDIN_FILENO);
	dup2(parsed_node->outfile, STDOUT_FILENO);
}

void open_pipefds(t_hold *hold)
{
	
}

void executer(t_hold *hold)
{
	int32_t *pids;
	int32_t pipegroups;
	int32_t	i;
	t_parsed_chunk *parsed_node;
	int32_t pipe_fds[MAX_FD][2];

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
	open_pipefds(hold, pipegroups, pipe_fds);

	i = 0;
	while (i < pipegroups)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			// redirection (dup2())
			redirection(parsed_node, i, pipegroups, pipe_fds);

write(2, "YES\n", 4);

			// close filediscriptors (pipes and files)
			close_fds(parsed_node, pipegroups, pipe_fds);
write(2, "2  YES\n", 7);
			// execute command
			execute_cmd(parsed_node, ori_env);
write(2, "3  YES\n", 7);
		}
		write(2, "something\n", 10);
		waitpid(pids[i], NULL, 0);
		i++;
		parsed_node = parsed_node->next;
	}
	// loop where we wait for kiddos to finish
	// i=0;
	// while ((i < pipegroups) && (pids[i]))
	// {
	// 	waitpid(pids[i], NULL, 0);
	// 	i++;
	// }
	write(2, "end\n", 4);
	free(pids);
}