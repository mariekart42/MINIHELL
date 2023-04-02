/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:21:16 by mmensing          #+#    #+#             */
/*   Updated: 2023/04/02 21:21:16 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_var(t_hold **hold, char *var, char *structure)
{
	t_env_exp	*tmp;
	t_env_exp	*prev;

	if (ft_strncmp(structure, "env", 3) == 0)
		tmp = (*hold)->env_list;
	if (ft_strncmp(structure, "export", 6) == 0)
		tmp = (*hold)->export_list;
	if (tmp != NULL && (ft_strncmp(tmp->item, var, ft_strlen(var)) == 0))
	{
		(*hold)->env_list = tmp->next;
		return ;
	}
	while (tmp != NULL && (ft_strncmp(tmp->item, var, ft_strlen(var)) != 0))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = tmp->next;
	free(tmp->item);
	tmp->item = NULL;
	free(tmp);
	tmp = NULL;
}

bool	find_var(t_hold *hold, char *var, char *structure)
{
	t_env_exp	*tmp;
	bool		var_exist;

	var_exist = false;
	if (ft_strncmp(structure, "env", 3) == 0)
		tmp = hold->env_list;
	if (ft_strncmp(structure, "export", 6) == 0)
		tmp = hold->export_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->item, var, ft_strlen(var)) == 0)
		{
			var_exist = true;
			delete_var(&hold, var, structure);
		}
		tmp = tmp->next;
	}
	return (var_exist);
}

void	first_char_is_num(t_pars *parsed_node, int i)
{
	if (ft_isdigit(parsed_node->args[i][0]) != 0)
	{
		exit_status("unset:", parsed_node->args[i],
			": not a valid identifier", 1);
	}
}

void	character_is_invalid(t_pars *parsed_node, int i, int j)
{
	if (ft_isalnum_mod(parsed_node->args[i][j]) == 0)
	{
		exit_status("unset:", parsed_node->args[i],
			": not a valid identifier", 1);
	}
}

void	unset_builtin(t_hold *hold, t_pars *parsed_node)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (parsed_node->args[i])
	{
		first_char_is_num(parsed_node, i);
		while (parsed_node->args[i][j] != '\0')
		{
			character_is_invalid(parsed_node, i, j);
			j++;
		}
		find_var(hold, parsed_node->args[i], "export");
		find_var(hold, parsed_node->args[i], "env");
		j = 0;
		i++;
	}
}
