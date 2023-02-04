#include "../head/minishell.h"

void executer(t_hold *hold)
{
	if (hold->exit_code != 0)
		return ;
	
}

int main(int32_t argc, char **argv, char **env)
{
	t_hold	*hold = NULL;
	(void)argc++;
	(void)argv++;
	(void)env++;
	

	hold = (t_hold*)malloc(sizeof(t_hold));
	if (!hold)
		return (1);
	hold->lexed_list = (t_lexing*)malloc(sizeof(t_lexing));
	if (!hold->lexed_list)
		return (1);
	hold->lexed_list = NULL;
	hold->exit_code = 0;
	// using signal function here to catch signal if eg ctr-c is used

	while (1)
	{
		hold->line = readline("MINIHELL> ");
		if (!hold->line)
			break ;

		lexer(hold);
		parser(hold);
		if (hold->exit_code == 0)
			print_macro_list(hold->lexed_list);
		
		// executer(hold);

		// if (line && *line)	// if line exist and is not empty, stuff gets saved in history list
		// 	add_history(line);

		freeList(hold->lexed_list);
		hold->lexed_list = NULL;
		free(hold->line);

	}
	//free(line);
}


//GENERAL:
// - add history stuff

// - create env/export list


//LEXER:


//PARSER:
// !do env/export shit in parser first

// - throw error if redir signs at the very end --> do in parser


//EXECUTER:
// - include pipex approach and test stuff