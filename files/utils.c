#include "../head/minishell.h"

void freeList(t_lexing* head)
{
   t_lexing* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

/* function adds node at the end of 'lexed_list'
 * checks if list is NULL -> appends node at the beginning			*/
void add_node_lex(t_hold *hold, char *content)
{
	t_lexing *ptr;


	ptr = (t_lexing *)malloc(sizeof(t_lexing));
	if (!ptr)
		return (exit_status(hold, "Error! Failed to malloc\n", 69));
	ptr->item = content;
	ptr->next = NULL;

	if (hold->lexed_list == NULL)
	{
		hold->lexed_list = ptr;
	}
	else
	{
		(last_node_lex(hold->lexed_list))->next = ptr;
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

void exit_status(t_hold *hold, char *message, int8_t exit_code_)
{
	write(2, message, ft_strlen(message));
	hold->exit_code = exit_code_;
}


