#include "minishell.h"

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
		free(tmp->var_name);
		tmp->var_name = NULL;
		free(tmp->var_value);
		tmp->var_value = NULL;
		free(tmp);
		tmp = NULL;
	}
}

//	- - - -  for LEX struct  - - - - - - - - - - - - - - 
/* function adds node at the end of 'lex_struct'
 * checks if list is NULL -> appends node at the beginning			*/
void	add_node_lex(t_hold *hold, char *content)
{
	t_lex	*ptr;

	ptr = (t_lex *)malloc(sizeof(t_lex));
	ptr->item = ft_strdup(content);
	ptr->next = NULL;
	if (hold->lex_struct == NULL)
		hold->lex_struct = ptr;
	else
		(last_node_lex(hold->lex_struct))->next = ptr;
}

t_lex	*last_node_lex(t_lex *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
