/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:40:27 by mmensing          #+#    #+#             */
/*   Updated: 2023/04/04 12:43:04 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_env(t_hold *hold)
{
	t_env_exp	*env_node;

	env_node = hold->env_list;
	while (env_node)
	{
		hold->my_env = append_string(hold->my_env, env_node->item);
		env_node = env_node->next;
	}
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
			exit_status(" :command not found!", "", "", 69);
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
			executer(&hold);
			free_content(&hold);
		}
		init_error_code(&hold);
	}
}
