/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_content_cont.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:40:17 by mmensing          #+#    #+#             */
/*   Updated: 2023/04/04 12:42:24 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* function frees all nodes of linked list 'lexed_list'
 * and all its variables:
 *	-> item 					*/
void	free_list_lex(t_lex *head)
{
	t_lex	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp->item)
			free(tmp->item);
		tmp->item = NULL;
		if (tmp)
			free(tmp);
		tmp = NULL;
	}
}

void	free_list_pars_helper(t_pars *tmp)
{
	unlink("tmp.hd");
	if (tmp->here_doc_delim)
		free(tmp->here_doc_delim);
	tmp->here_doc_delim = NULL;
}

void	free_list_pars_tmp(t_pars *tmp)
{
	if (tmp->args)
		free(tmp->args);
	tmp->args = NULL;
	if (tmp)
		free(tmp);
	tmp = NULL;
}

/* function frees all nodes of linked list 'pars_list'
 * and all its variables:
 *	-> args, cmd_path 					*/
void	free_list_pars(t_pars *head)
{
	t_pars	*tmp;
	int32_t	i;

	i = 0;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp->cmd_path)
			free(tmp->cmd_path);
		tmp->cmd_path = NULL;
		if (tmp->here_doc_delim != NULL)
			free_list_pars_helper(tmp);
		while (tmp->args[i] != NULL)
		{
			if (tmp->args[i])
				free(tmp->args[i]);
			tmp->args[i] = NULL;
			i++;
		}
		free_list_pars_tmp(tmp);
		i = 0;
	}
}

void	free_list_env_export(t_env_exp *head)
{
	t_env_exp	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->item);
		free(tmp);
		tmp = NULL;
	}
}
