#include "../head/minishell.h"

void free_list_lex(t_lexing* head)
{
   t_lexing* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

void free_list_data(t_data* head)
{
   t_data* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
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
	ptr->item = content;
	ptr->next = NULL;

	if (hold->lex_struct == NULL)
	{
		printf(YEL"IS NULL\n"RESET);
		hold->lex_struct = ptr;
	}
	else
	{
		printf(MAG"IS NOT NULL\n"RESET);
		(last_node_lex(hold->lex_struct))->next = ptr;
	}
}

t_lexing	*last_node_lex(t_lexing *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

//	- - - -  for ARGS struct  - - - - - - - - - - - - - - 
/* function adds node at the end of 'lex_struct'
 * checks if list is NULL -> appends node at the beginning			*/
void add_node_data(t_hold *hold, char **content, char	*type)
{
	t_data *ptr;


	ptr = (t_data *)malloc(sizeof(t_data));
	if (!ptr)
		return (exit_status(hold, "Error! Failed to malloc\n", 69));
	if(ft_strncmp(type, "arg", 3)==0)
		ptr->arg_array = content;
	else if(ft_strncmp(type, "env", 3)==0)
		ptr->env_array = content;
	ptr->next = NULL;
	if (hold->data_struct == NULL)
	{
		// printf(YEL"IS NULL\n"RESET);
		hold->data_struct = ptr;
	}
	else
	{
		// printf(MAG"IS NOT NULL\n"RESET);
		(last_node_data(hold->data_struct))->next = ptr;
	}
}

t_data	*last_node_data(t_data *lst)
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
	write(2, message, ft_strlen(message));
	hold->exit_code = exit_code_;
}



