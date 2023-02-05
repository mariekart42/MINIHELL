#include "../head/minishell.h"

void executer(t_hold *hold)
{
	if (hold->exit_code != 0)
		return ;
	if ()
}

int main(int32_t argc, char **argv, char **env)
{
	t_hold	*hold = NULL;
	(void) argc;
	(void) argv;
	(void) env;

	hold = (t_hold *)malloc(sizeof(t_hold));
	if (!hold)
		return (69);
	hold->lexed_list = (t_lexing*)malloc(sizeof(t_lexing));
	if (!hold->lexed_list)
		return (69);

	hold->lexed_list = NULL;
	hold->exit_code = 0;
	
	// using signal function here to catch signal if eg ctr-c is used

	while (1)
	{
		hold->line = readline("MINIHELL> ");
		if (!hold->line)
			break ;

		// add_history to update history with current line
		if (ft_strlen(hold->line) > 0)
			add_history(line);

		lexer(hold);
		parser(hold);
		if (hold->exit_code == 0)
			print_macro_list(hold->lexed_list);
		
		executer(hold);


		free(hold->line);
		freeList(hold->lexed_list);
		hold->lexed_list = NULL;

	}
	// here func to clear all memory
}


//GENERAL:
// - add history stuff -> move cursor bums

// - create env/export list

// - how to store prev return value for $?


//LEXER:


//PARSER:
// !do env/export shit in parser first

// - throw error if redir signs at the very end --> do in parser


//EXECUTER:
// - include pipex approach and test stuff


//LATER:
// - after main loop clear all memory

// - signals shit