#include "minishell.h"

// KeinDrama
// niemals

void free_content(t_hold *hold)
{
	free(hold->line);
	free_list_lex(hold->lex_struct);
	// free_list_data(hold->data_struct);
	hold->lex_struct = NULL;
	// hold->data_struct = NULL;

}

int32_t init_structs(t_hold **hold)
{
	(*hold) = (t_hold *)malloc(sizeof(t_hold));
	if (!(*hold))
		return (69);
	(*hold)->lex_struct = (t_lexing*)malloc(sizeof(t_lexing));
	if (!(*hold)->lex_struct)
		return (69);
	// (*hold)->data_struct = (t_data*)malloc(sizeof(t_data));
	// if (!(*hold)->data_struct)
	// 	return (69);
	(*hold)->env_list = (t_env_export*)malloc(sizeof(t_env_export));
	if (!(*hold)->env_list)
		return (69);
	(*hold)->export_list = (t_env_export*)malloc(sizeof(t_env_export));
	if (!(*hold)->export_list)
		return (69);
	(*hold)->parsed_list = (t_parsed_chunk*)malloc(sizeof(t_parsed_chunk));
	if (!(*hold)->parsed_list)
		return (69);
	(*hold)->lex_struct = NULL;
	// (*hold)->data_struct = NULL;
	(*hold)->env_list = NULL;
	(*hold)->export_list = NULL;
	(*hold)->parsed_list = NULL;
	return (0);
}

void free_env_export(t_hold *hold)
{
	
	free_list_env(hold->env_list);
	free_list_env(hold->export_list);
	hold->env_list = NULL;
	hold->export_list = NULL;

}

int main(int32_t argc, char **argv, char **env)
{
	t_hold	*hold = NULL;
	(void) argc;
	(void) argv;

	if (init_structs(&hold))
		return (69);

	// using signal function here to catch signal if eg ctr-c is used
	
	create_env_export_list(hold, env);
			// important later
			char *test;
			test = getenv("PATH");
			printf("getenv: %s\n", test);
			
	while (1)
	{
		hold->exit_code = 0;
		hold->line = readline(BLU"MINIHELL> "RESET);
		if (!hold->line)
			break ;

		// if line is empty, bash returns 0 and does nothing
		if (ft_strlen(hold->line) > 0)
		{
			add_history(hold->line);

			lexer(hold);
			parser(hold);
			cd_builtin(hold, hold->parsed_list)
			// exit(0);
			// if (hold->exit_code == 0)
			// 	print_macro_list(hold->lex_struct);
			// executer(hold);
// printf("after executer | EXIT\n\n");
// exit(0);
			free_content(hold);
		}
	}
	free_env_export(hold);
	clear_history();
	// here func to clear all memory
}

//!!!NEXT:
// - executer: what if there is more then one outfile/infile? -> testing
// - parser done for now, start executing (redirection, forking)
// - look again into wait/-pid function


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//!  GENERAL:
// - move cursor bums
// - how to store prev return value for '$?' ?
// - handle also relativ paths


//!  LEXER: √

//!  PARSER:
// - !do env/export shit in parser first
// - parser keeps all quote symbols -> need later or should get removed/skipped in parser?


//!  EXECUTER:
//		- forking √
//		- wait 4 kiddos
//		- redirections √ (guess thats it)
//		- executing
//		- create pipes NEXT


//!  BUILTINS:
// - later: put builtin stuff into executer (not as bool in main!)
// - builtins:
//		- env √
//		- export -> sorting works, add handling path-updating
//		- pwd √
//		- cd -> add handling path-updating
//		- unset
//		- echo
//		- exit


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//!  LATER:
// - after main loop clear all memory
// - exit with exit command -> returns 0
// - signals shit

// - - -
//!  CONCERNINGSITUATIONS:
//
//
//
//