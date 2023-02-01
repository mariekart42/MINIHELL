#include "../head/minishell.h"

void recognize_type(t_hold *hold)
{
	
}

void parser(t_hold *hold)
{
	recognize_type(hold);
}

int main(int32_t argc, char **argv, char **env)
{
	t_hold	*hold;

	hold = (t_hold*)malloc(sizeof(t_hold));
	if (!hold)
		return (1);

	// using signal function here to catch signal if eg ctr-c is used
argc++;
argv++;
	while (1)
	{
		hold->line = readline("MINIHELL> ");
		if (!hold->line)
			break ;

		lexer(hold);
		parser(hold);
		print_list(hold->lexed_list, "yee");
		
		// if (line && *line)	// if line exist and is not empty, stuff gets saved in history list
		// 	add_history(line);

		freeList(hold->lexed_list);
		hold->lexed_list = NULL;
		free(hold->line);		
	}
	//free(line);
}


//GENERAL:
// - change from exiting on errors to return to main loop
//		-> set flag in struct, do nothing in lexer, parser, executer and return to main loop

// - add history stuff


//LEXER:


//PARSER:
// !do env/export shit in parser first

// - write recognize function -> sets specific MACROS to the single nodes
// 		eg. node with content pipe symbol gets macro 'PIPE'

// - redir function throw error if redir signs at the very end --> do it in parser


//EXECUTER: