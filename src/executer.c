#include "../inc/minishell.h"

void executer(t_hold *hold)
{
	if (hold->exit_code != 0)
		return ;
	print_parsed_list(hold->parsed_list);

	int32_t pipegroups;

	pipegroups = count_pipegroups(hold->lex_struct);
	printf("am pipes: %d\n", pipegroups);
	// handle always one pipegroup

	// create and malloc array with process-id's for forking
	// open amount of pipes we need (one pipegroup = one pipe)
	while (pipegroups > 0)
	{
		// fork, if pid is 0:
			// redirection (dup2())
			// close filediscriptors (pipes and files)
			// execute command

		pipegroups--;
	}
	// loop where we wait for kiddos to finish
}