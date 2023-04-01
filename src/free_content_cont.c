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
}

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
		free(tmp->item);
		tmp->item = NULL;
		free(tmp);
		tmp = NULL;
	}
}

void	free_list_pars_helper(t_pars *tmp)
{
	unlink("tmp.hd");
	free(tmp->here_doc_delim);
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
		free(tmp->cmd_path);
		tmp->cmd_path = NULL;
		if (tmp->here_doc_delim != NULL)
		{
			free_list_pars_helper(tmp);
			tmp->here_doc_delim = NULL;
		}
		while (tmp->args[i] != NULL)
		{
			free(tmp->args[i]);
			tmp->args[i] = NULL;
			i++;
		}
		free(tmp->args);
		tmp->args = NULL;
		i = 0;
		free(tmp);
		tmp = NULL;
	}
}

void	free_list_env_export(t_env_exp *head)
{
	t_env_exp	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
		tmp = NULL;
	}
}
