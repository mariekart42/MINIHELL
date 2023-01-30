# include "../head/minishell.h"

void print_list(t_lexing *list, char *name)
{
	printf("----------\n[%s]:\n", name);
	if(list == NULL)
	{
		printf("list_pos_1: (NULL)\n");
		return ;
	}
	int32_t i = 1;
	t_lexing *node = NULL;
	node = list;
	while (node->next != NULL)
	{
		printf("list_pos_%d: %s\n", i, node->item);
		i++;
		node = node->next;
	}
	printf("list_pos_%d: %s\n", i, node->item);
	i++;
	if(node->next == NULL)
		printf("list_pos_%d: (NULL)\n", i);
	else	
		printf("something wrong! (print_list function)\n");
	printf("-- done --\n\n");
}