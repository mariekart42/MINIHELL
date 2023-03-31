#include "minishell.h"

void	free_main(t_hold **hold)
{
	free_env_export(*hold);
	free(*hold);
	free(hold);
	clear_history();
}

int32_t	prep_minihell(t_hold *hold)
{
	g_error_code = 0;
	hold->line = readline(BLU"MINIHELL> "RESET);
	if (!hold->line)
	{
		ft_putstr_fd("\b\bexit\n", 1);
		exit(1);
	}
	if (ft_strlen(hold->line) > 0)
		return (1);
	else
		return (0);
}

void	init_error_code(t_hold *hold)
{
	if (g_error_code > 255)
		hold->prev_error = g_error_code % 255;
	else
		hold->prev_error = g_error_code;
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
		if (prep_minihell(hold))
		{
			add_history(hold->line);
			lexer(hold);
			parser(hold);
			executer(hold, env);
			free_content(&hold);
			init_error_code(hold);
		}
	}
	free_main(&hold);
	free(hold);
	hold = NULL;
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
