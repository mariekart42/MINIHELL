#include "minishell.h"

void	free_exit(t_hold *hold)
{
	if (hold->line)
		free(hold->line);
	if (hold->lex_struct)
		free_list_lex(hold->lex_struct);
	if (hold->pars_list)
		free_list_pars(hold->pars_list);
	if (hold->env_list)
		free_list_env_export(hold->env_list);
	if (hold->export_list)
		free_list_env_export(hold->export_list);
	free_main();
}

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
	if (ft_strlen(hold->line) == 1 && hold->line[0] == ':')
	{
		free(hold->line);
		return (0);
	}
	if (ft_strlen(hold->line) > 0)
		return (1);
	else
	{
		free(hold->line);
		return (0);
	}
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
			// print_list(hold.lex_struct, "aieuhf");
			parser(&hold);
			// print_macro_list(hold.lex_struct);
			executer(&hold, env);
			free_content(&hold);
		}
		init_error_code(&hold);
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

//!  PROBLEMOS:
//	
