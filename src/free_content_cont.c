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
		{
			free_list_pars_helper(tmp);
			tmp->here_doc_delim = NULL;
		}
		while (tmp->args[i] != NULL)
		{
			if (tmp->args[i])
				free(tmp->args[i]);
			tmp->args[i] = NULL;
			i++;
		}
		if (tmp->args)
			free(tmp->args);
		tmp->args = NULL;
		i = 0;
		if (tmp)
			free(tmp);
		tmp = NULL;
	}
}

/* function frees all nodes of linked list 'env_list' or 'export_list'
 * and all its variables:
 *	-> item, var_name, var_value				*/
void	free_list_env_export(t_env_exp *head)
{
	t_env_exp	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp->var_name)
			free(tmp->var_name);
		tmp->var_name = NULL;
		if (tmp->var_value)
			free(tmp->var_value);
		tmp->var_value = NULL;
		if (tmp)
			free(tmp);
		tmp = NULL;
	}
}
