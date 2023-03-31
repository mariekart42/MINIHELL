#include "minishell.h"

void	free_main(t_hold *hold)
{
	free_env_export(hold);
	free(hold);
	clear_history();
}

void	exit_when_no_line(char *line)
{
	if (!line)
	{
		ft_putstr_fd("\b\bexit\n", 1);
		exit(1);
	}
}

int	main(int32_t argc, char **argv, char **env)
{
	t_hold	*hold;

	hold = NULL;
	if (init_structs(&hold, argv, argc))
		return (69);
	create_env_export_list(hold, env);
	signals();
	while (1)
	{
		g_error_code = 0;
		hold->line = readline(BLU"MINIHELL> "RESET);
		exit_when_no_line(hold->line);
		if (ft_strlen(hold->line) > 0)
		{
			add_history(hold->line);
			lexer(hold);
			// print_list(hold->lex_struct, "fuck");
			parser(hold);
			executer(hold, env);
			fprintf(stderr, MAG"error code: %d\n"RESET, g_error_code);
			free_content(&hold);
			// free(hold->line);
			// hold->line = NULL;
		}
	}
	free_main(hold);
}

//!!!NEXT:
// - change permissions for open in and outfile

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//!  GENERAL:
// - move cursor bums
// - handle also relativ paths

//!  LEXER: √

//!  PARSER:√

//!  EXECUTER:
// - change 'ori_env' to **char of own env list

//!  LEAKS:

//!  PROBLEMOS:
//	- |			-> 2 error msgs, no sure if i can comment out the sec one (very bottom of lexer)
//	- echo $?? 	-> output is with space, guess not that important
