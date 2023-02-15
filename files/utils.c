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

void free_list_env(t_env_export* head)
{
   t_env_export* tmp;

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
		// printf(YEL"IS NULL\n"RESET);
		hold->lex_struct = ptr;
	}
	else
	{
		// printf(MAG"IS NOT NULL\n"RESET);
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

//	- - - -  for ENV struct  - - - - - - - - - - - - - - 
t_env_export *new_node_env(void)
{
	t_env_export *tmp;

	tmp = (t_env_export*)malloc(sizeof(t_env_export));
	tmp->next = NULL;
	return (tmp);
}

t_env_export *add_node_env(t_hold *hold, char *content, char *type)
{
	t_env_export *tmp;
	t_env_export *p;

	tmp = new_node_env();
	tmp->item = content;
	if (ft_strncmp(type, "env", 3) == 0)
	{
		if (hold->env_list == NULL)
			hold->env_list = tmp;
		else
		{
			p = hold->env_list;
			while(p->next != NULL)
				p = p->next;
			p->next = tmp;
		}
		return (hold->env_list);
	}
	else
	{
		if (hold->export_list == NULL)
			hold->export_list = tmp;
		else
		{
			p = hold->export_list;
			while(p->next != NULL)
				p = p->next;
			p->next = tmp;
		}
		return (hold->export_list);
	}
}

void sort_export_list(t_hold *hold)
{
	t_env_export *tmp;

	// sort list alphabetically
	t_env_export *p1;
	t_env_export *p2;
tmp = NULL;
p1 = hold->export_list;
p2 = hold->export_list->next;
	while (p1->next != NULL)
	{
		while (p2 != NULL)
		{
			if (ft_strncmp(p1->item, p2->item, ft_strlen(p2->item)) > 0)// means first is bigger then seccond
			{
				ft_strlcpy(tmp->item, p1->item, 9999);
printf(GRN"check\n"RESET);
exit(0);
				ft_strlcpy(p1->item, p2->item, 9999);
				ft_strlcpy(p2->item, tmp->item, 9999);
				// tmp->item = p1->item;
				// p1->item = p2->item;
				// p2->item = tmp->item;
				// tmp = NULL;
				// swap
			}
			p2 = p2->next;
		}
		p1 = p1->next;
		p2 = p1->next;
	}
	

	tmp = hold->export_list;

	// adding 'declare -x' infront of everything
	while (tmp != NULL)
	{
		tmp->item = ft_strjoin("declare -x ", tmp->item);
		tmp = tmp->next;
	}
}

void create_env_export_list(t_hold *hold, char **ori_env)
{
	int32_t env_len = 0;
	t_env_export *tmp_env;
	t_env_export *tmp_export;

	tmp_env = hold->env_list;
	tmp_export = hold->export_list;
	while (ori_env[env_len] != NULL)
	{
		hold->env_list = add_node_env(hold, ori_env[env_len], "env");
		hold->export_list = add_node_env(hold, ori_env[env_len], "export");
		env_len++;
	}
	sort_export_list(hold);
}

//	- - - -  for ARGS struct  - - - - - - - - - - - - - - 
/* function adds node at the end of 'lex_struct'
 * checks if list is NULL -> appends node at the beginning			*/
void add_node_data(t_hold *hold, char **content)
{
	t_data *ptr;


	ptr = (t_data *)malloc(sizeof(t_data));
	if (!ptr)
		return (exit_status(hold, "Error! Failed to malloc\n", 69));
	ptr->arg_array = content;
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



