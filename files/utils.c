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

	ptr = (t_lexing *)malloc(sizeof(ptr));
	if (!ptr)
		exit_status("Error! Failed to malloc\n", 69);
	ptr->item = content;
	ptr->next = NULL;

	if (hold->lexed_list == NULL)
		hold->lexed_list = ptr;
	else
		(last_node_lex(hold->lexed_list))->next = ptr;
}

t_lexing	*last_node_lex(t_lexing *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void exit_status(char *message, int32_t exit_code)
{
	write(2, message, ft_strlen(message));
	exit(exit_code);
}

// t_lexing	*ft_lstnew_lex(void *content)
// {
// 	t_lexing	*ptr;

// 	ptr = (t_lexing *)malloc(sizeof(*ptr));
// 	if (ptr == NULL)
// 		return (NULL);
// 	ptr->item = content;
// 	ptr->next = NULL;
// 	return (ptr);
// }

// t_lexing	*ft_lstlast_lex(t_lexing *lst)
// {
// 	if (!lst)
// 		return (NULL);
// 	while (lst->next)
// 		lst = lst->next;
// 	return (lst);
// }


