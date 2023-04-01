#include "minishell.h"

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
