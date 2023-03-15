#include "minishell.h"

void free_content(t_hold **hold)
{

	// free((*hold)->line);
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
	hold->line = NULL;

	// using signal function here to catch signal if eg ctr-c is used
	
	// Take a look here on how to create export
	// Found in utils.c
	create_env_export_list(hold, env);
			// // important later
			// char *test;
			// test = getenv("PATH");
			// printf("getenv: %s\n", test);
	signals(); // Signals are applied before the main loop
	while (1)
	{
		error_code = 0;
		hold->line = readline(BLU"MINIHELL> "RESET);
		// hold->line = ft_strdup("ls -l");
		if (!hold->line)
		{
			// Signal for Ctrl+D
			ft_putstr_fd("\b\bexit\n", 1);
			exit(1);
		}
// 		// if line is empty, bash returns 0 and does nothing
		if (ft_strlen(hold->line) > 0)
		{
			add_history(hold->line);
			lexer(hold);
// print_list(hold->lex_struct, "lex");
			parser(hold);
// print_parsed_list(hold->parsed_list);
// print_macro_list(hold->lex_struct);
			executer(hold, env);

			printf(MAG"error code: %d\n"RESET, error_code);
			free_content(&hold);
			free(hold->line);
			hold->line = NULL;
		}
	}
	free_env_export(hold);
	free(hold);
	clear_history();
}


//!!!NEXT:
// - change permissions for open in and outfile

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//!  GENERAL:
// - move cursor bums
// - handle also relativ paths


//!  LEXER: √

//!  PARSER:√


//!  EXECUTER:
//	- douple redir not working yet(prolly wrong opening rights)
// - change 'ori_env' to **char of own env list


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//!  LATER:
// - exit with exit command -> returns 0
// - signals shit


//!  LEAKS:
// - in parser:
//		around 20 leaks (more if using more nodes)
//	-> deal with it later cause we need to restructure parser anyways a bit


//!  PROBLEMOS:
//!			SANTI:
//				-  echoHola				-> wrong output
//				-  echo-nHola			-> wrong output
//				-  pwd -p				-> wrong output (not sure if mandatory)
//				-  pwd --p				-> wrong output (not sure if mandatory)
//				-  cd ~					-> with space between wrong output

//!			MY:
//		    !!	-  cat Makefile | cat | cat				-> gets stuck
//				-  cat Makefile | grep src | cat -e		-> same shit
//				-  echo hola | cat -e | cat -e | cat -e -> gets stuck
