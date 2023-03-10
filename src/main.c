#include "minishell.h"

void free_content(t_hold **hold)
{
	free((*hold)->line);
	free_list_lex((*hold)->lex_struct);
	free_list_pars((*hold)->parsed_list);
	(*hold)->lex_struct = NULL;
	(*hold)->parsed_list = NULL;

}

int32_t init_structs(t_hold **hold)
{
	(*hold) = (t_hold *)malloc(sizeof(t_hold));
	if (!(*hold))
		return (69);
	(*hold)->env_list = NULL;
	(*hold)->parsed_list = NULL;
	(*hold)->export_list = NULL;
	(*hold)->lex_struct = NULL;
	return (0);
}

void free_env_export(t_hold *hold)
{
	free_list_env_export(hold->env_list);
	free_list_env_export(hold->export_list);
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
	
	// Take a look here on how to create export
	// Found in utils.c
	create_env_export_list(hold, env);
			// // important later
			// char *test;
			// test = getenv("PATH");
			// printf("getenv: %s\n", test);
			
	while (1)
	{
		hold->exit_code = 0;
		hold->line = readline(BLU"MINIHELL> "RESET);
		// hold->line = ft_strdup("ls -l");
		if (!hold->line)
			break ;

// 		// if line is empty, bash returns 0 and does nothing
		if (ft_strlen(hold->line) > 0)
		{
			add_history(hold->line);

			lexer(hold);
			// print_list(hold->lex_struct, "lex");
// write(2, "check\n", 6);
			parser(hold);
			// print_macro_list(hold->lex_struct);
			// print_parsed_list(hold->parsed_list);
// write(2, "check\n", 6);
// 			// if (hold->exit_code == 0)
// 			// 	print_macro_list(hold->lex_struct);
// print_parsed_list(hold->parsed_list);
// printf("delim: %s\n", hold->parsed_list->access.delim);
// printf("delim: %s\n", hold->parsed_list->next->access.delim);
// exit(0);
			executer(hold, env);
			// builtin(hold, hold->parsed_list); // Add for testing
			free_content(&hold);
		}
	}
	free_env_export(hold);
	free(hold);
	clear_history();
}



//!!!NEXT:
// - shit should work in a loop
// - executer: what if there is more then one outfile/infile? -> testing
// - parser done for now, start executing (redirection, forking)
// - look again into wait/-pid function


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//!  GENERAL:
// - move cursor bums
// - how to store prev return value for '$?' ?
// - handle also relativ paths


//!  LEXER: ???

//!  PARSER:
// - !do env/export shit in parser first
// - parser keeps all quote symbols -> need later or should get removed/skipped in parser?
// - cat <<		-> throw syntax error


//!  EXECUTER:
//	- douple redir not working yet(prolly wrong opening rights)
// - change 'ori_env' to **char of own env list
// - include builtins as soon as they're finished


//!  BUILTINS:
// - later: put builtin stuff into executer (not as bool in main!)
// - builtins:
//		- env ???
//		- export -> sorting works, add handling path-updating
//		- pwd ???
//		- cd -> add handling path-updating
//		- unset
//		- echo
//		- exit


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//!  LATER:
// - after main loop clear all memory
// - exit with exit command -> returns 0
// - signals shit

//!  LEAKS:
// - in parser:
//		around 20 leaks (more if using more nodes)
//	-> deal with it later cause we need to restructure parser anyways a bit


//!  PROBLEMOS:
//!			SANTI:
//				-  echo brrr			-> doesnt prints first character
//				-  echo "brr"			-> same problem plus prints quotations (more a parser problem)
//				-  echoHola				-> wrong output
//				-  pwd -p				-> wrong output
//				-  pwd --p				-> wrong output
//				-  echo | echo			-> free stuff error
//				-  echo hello | rev		-> gets stuck
//				-  cd src obj			-> should give error, but goes to src
//				-  cd ~					-> with space between wrong output

//!			MY:
//				-  cat Makefile | cat -e | cat -e		-> gets stuck
//				-  ls -la | grep "."					-> parsing problem, reads and interprets quotes as actual characters
//				-  cat Makefile | grep src | cat -e		-> same shit
