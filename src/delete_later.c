# include "minishell.h"

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

void print_list(t_lex *list, char *name)
{
printf("----------\n[%s]:\n", name);
if(list == NULL)
{
	printf("list_pos_1: (NULL)\n");
	return ;
}
int32_t i = 1;
t_lex *node = NULL;
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

void print_macro_list(t_lex *list)
{
printf("----------\n\n");
if(list == NULL)
{
	printf(MAG"list_pos_1: (NULL)\n"RESET);
	return ;
}
int32_t i = 1;
t_lex *node = NULL;
node = list;
while (node->next != NULL)
{
	printf("list_pos_%d: "WHT" %s\t\t"YEL"%s\n"RESET, i, node->item, return_macro(node->macro));
	i++;
	node = node->next;
}
printf("list_pos_%d: "WHT" %s\t\t"YEL"%s\n"RESET, i, node->item, return_macro(node->macro));
i++;
if(node->next == NULL)
	printf("list_pos_%d: "MAG" (NULL)\n"RESET, i);
else	
	printf("something wrong! (print_list function)\n");
printf("-- done --\n\n");
}
void print_export(t_hold *hold)
{
	t_env_exp *tmp = hold->export_list;
	while (tmp != NULL)
	{
		printf(RED"%s\n"RESET, tmp->item);
		tmp = tmp->next;
	}
}

void print_parsed_list(t_pars *pars)
{
	t_pars *tmp_pars = pars;
	int i = 0;
	int k = 1;
	printf(RED"\n    print_parsed_list" RESET);
	while (tmp_pars != NULL)
	{
		printf("\n - - - PIPEGROUP %d - - - \n", k);
		printf(YEL"args:     "RESET);
		while (tmp_pars->args[i] != NULL)
		{
			printf(YEL"%s  "RESET, tmp_pars->args[i]);
			i++;
		}
		printf("\n");
		if(tmp_pars->infile == 0)
			printf(GRN"infile:   stdin\n"RESET);
		else
			printf(GRN"infile:   %d\n"RESET, tmp_pars->infile);
		if(tmp_pars->outfile==1)
			printf(CYN"outfile:   stdout\n"RESET);
		else
			printf(CYN"outfile:  %d\n"RESET, tmp_pars->outfile);
		printf(MAG"cmdpath:  %s\n"RESET, tmp_pars->cmd_path);
		i = 0;
		k++;
		tmp_pars = tmp_pars->next;
	}
	printf(RED"------------------------\n\n"RESET);
}