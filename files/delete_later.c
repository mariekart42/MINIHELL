# include "../head/minishell.h"

char *return_macro(int32_t m)
{
	if (m==0)
		return("BUILTIN");
	if (m==1)
		return("WORD");
	if (m==2)
		return("SING_QUOTE");
	if (m==3)
		return("DOUBL_QUOTE");
	if (m==4)
		return("PIPE");
	if (m==5)
		return("SING_OPEN_REDIR");
	if (m==6)
		return("SING_CLOSE_REDIR");
	if (m==7)
		return("DOUBL_OPEN_REDIR");
	if (m==8)
		return("DOUBL_CLOSE_REDIR");
	else
		return("ERROR PRINTING MACRO");
}

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

void print_macro_list(t_lexing *list)
{
	printf("----------\n\n");
	if(list == NULL)
	{
		printf("list_pos_1: (NULL)\n");
		return ;
	}
	int32_t i = 1;
	t_lexing *node = NULL;
	node = list;
			printf(GRN"check\n"RESET);

	while (node->next != NULL)
	{
		printf("list_pos_%d: %s\t\t"YEL"%s\n"RESET, i, node->item, return_macro(node->macro));
		i++;
		node = node->next;
	}
	printf("list_pos_%d: %s\t\t"YEL"%s\n"RESET, i, node->item, return_macro(node->macro));
	i++;
	if(node->next == NULL)
		printf("list_pos_%d: (NULL)\n", i);
	else	
		printf("something wrong! (print_list function)\n");
	printf("-- done --\n\n");
}