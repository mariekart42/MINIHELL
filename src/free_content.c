/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:40:19 by mmensing          #+#    #+#             */
/*   Updated: 2023/04/04 12:43:14 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_main(void)
{
	int32_t	i;

	i = 3;
	while (i < MAX_FD)
	{
		close(i);
		i++;
	}
	clear_history();
}

void	free_content(t_hold *hold)
{
	if (hold->line)
		free(hold->line);
	if (hold->my_env)
	{
		free(hold->my_env);
		hold->my_env = NULL;
	}
	hold->line = NULL;
	if (hold->lex_struct)
		free_list_lex(hold->lex_struct);
	hold->lex_struct = NULL;
	if (hold->pars_list)
		free_list_pars(hold->pars_list);
	hold->pars_list = NULL;
}

void	free_env_path(char **env_path)
{
	int32_t	i;

	i = 0;
	while (env_path[i])
	{
		free(env_path[i]);
		env_path[i] = NULL;
		i++;
	}
	if (env_path)
	{
		free(env_path);
		env_path = NULL;
	}
}

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
