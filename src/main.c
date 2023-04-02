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

bool only_spaces(char *line)
{
	int32_t	i;

	i = 0;
	if (line[skip_spaces(line, i)] == '\0')
		return (true);
	else
		return (false);
}

bool	line_is_nothing(char *line)
{
	int32_t	i;

	i = 0;
	i = skip_spaces(line, i);
	if (line[i] == '\0')
		return (true);
	if (line[i] == ':')
		return (true);
	if ((line[i] == '\'' && line[i + 1] == '\'') \
		|| (line[i] == '\"' && line[i + 1] == '\"'))
	{
		i = skip_spaces(line, i + 2);
		if (line[i] == '\0')
		{
			exit_status(": :command not found!", "", "", 69);
			return (true);
		}
	}
	return (false);

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
	if (line_is_nothing(hold->line) == true)
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
			parser(&hold);
			executer(&hold, env);
			free_content(&hold);
		}
		init_error_code(&hold);
	}
}
