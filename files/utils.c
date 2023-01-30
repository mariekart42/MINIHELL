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

void exit_status(char *message, int32_t exit_code)
{
	write(2, message, ft_strlen(message));
	exit(exit_code);
}

t_lexing	*ft_lstnew_lex(void *content)
{
	t_lexing	*ptr;

	ptr = (t_lexing *)malloc(sizeof(*ptr));
	if (ptr == NULL)
		return (NULL);
	ptr->item = content;
	ptr->next = NULL;
	return (ptr);
}

t_lexing	*ft_lstlast_lex(t_lexing *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
