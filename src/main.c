#include "minishell.h"

int32_t	prep_minihell(t_hold *hold)
{
	hold->line = readline(BLU"MINIHELL> "RESET);
	if (!hold->line)
	{
		free_exit(hold);
		ft_putstr_fd("\b\b exit\n", 1);
		exit(g_error_code);
	}
	g_error_code = 0;
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
	t_hold	hold;

	g_error_code = 0;
	if (init_structs(&hold, argv, argc))
		return (69);
	create_env_export_list(&hold, env);
	signals();
	while (1)
	{
		if (prep_minihell(&hold))
		{
			add_history(hold.line);
			lexer(&hold);
			// print_list(hold.lex_struct, "ksjdfgh");
			parser(&hold);
			// print_macro_list(hold.lex_struct);
			executer(&hold, env);
			free_content(&hold);
			init_error_code(&hold);
		}
	}
}


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//!  GENERAL:
// - move cursor bums
// - handle also relativ paths

//!  LEXER: √

//!  PARSER:√

//!  EXECUTER:
// - change 'ori_env' to **char of own env list

//!  LEAKS:
// 2,200 bytes in 62 blocks

//!  PROBLEMOS:
//	
