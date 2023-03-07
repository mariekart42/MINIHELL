#include "minishell.h"

/* function frees all nodes of linked list 'parsed_chunk'
 * and all its variables:
 *	-> args, cmd_path 					*/
void free_list_pars(t_parsed_chunk* head)
{
	t_parsed_chunk* tmp;
	int32_t i;

	i = 0;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->cmd_path);
		while (tmp->args[i] != NULL)
		{
			free(tmp->args[i]);
			i++;
		}
		i = 0;
		free(tmp);
	}
}

/* function frees all nodes of linked list 'lexed_list'
 * and all its variables:
 *	-> item 					*/
void free_list_lex(t_lexing* head)
{
   t_lexing *tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->item);
		free(tmp);
    }
}

/* function frees all nodes of linked list 'env_list' or 'export_list'
 * and all its variables:
 *	-> item, var_name, var_value				*/
void free_list_env_export(t_env_export* head)
{
	t_env_export* tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->item); // maybe delete
		free(tmp->var_name);
		free(tmp->var_value);
		free(tmp);
	}
}

//	- - - -  for LEX struct  - - - - - - - - - - - - - - 
/* function adds node at the end of 'lex_struct'
 * checks if list is NULL -> appends node at the beginning			*/
void add_node_lex(t_hold *hold, char *content)
{
	t_lexing *ptr;

	ptr = (t_lexing *)malloc(sizeof(t_lexing));
	if (!ptr)
		return (exit_status(hold, "Error! Failed to malloc\n", 69));
	ptr->item = ft_strdup(content);
	ptr->next = NULL;

	if (hold->lex_struct == NULL)
		hold->lex_struct = ptr;
	else
		(last_node_lex(hold->lex_struct))->next = ptr;
}

t_lexing	*last_node_lex(t_lexing *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

//  - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
void exit_status(t_hold *hold, char *message, int8_t exit_code_)
{
	// printf(RED"calling exit_status: %d\n"RESET, exit_code_);
	write(2, message, ft_strlen(message));
	hold->exit_code = exit_code_;
}
