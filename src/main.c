#include "minishell.h"

int main(int32_t argc, char **argv, char **env)
{
	t_hold	*hold;

	hold = NULL;
	if (init_structs(&hold, argv, argc))
		return (69);
	create_env_export_list(hold, env);
	signals();
	while (1)
	{
		error_code = 0;
		hold->line = readline(BLU"MINIHELL> "RESET);
		if (!hold->line)
		{
			ft_putstr_fd("\b\bexit\n", 1);
			exit(1);
		}
		if (ft_strlen(hold->line) > 0)
		{
			add_history(hold->line);
			lexer(hold);
			parser(hold);
			executer(hold, env);
			fprintf(stderr, MAG"error code: %d\n"RESET, error_code);
			free_content(&hold);
			// free(hold->line);
			// hold->line = NULL;
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
// - change 'ori_env' to **char of own env list


//!  LEAKS:



//!  PROBLEMOS:
//		-  ls|exit 42		-> wrong error 

