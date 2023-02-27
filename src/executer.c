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
	while (pipegroups > 0)
	{
		// open pipes

		// redirection

		// fork
		pipegroups--;
	}
}