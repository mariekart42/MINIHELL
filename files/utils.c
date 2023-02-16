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

// void swap_nodes(t_hold **hold, t_env_export *x_, t_env_export *y_)
// {

 
//     // Search for x (keep track of prevX and currX)
//     t_env_export* prev_p1 = NULL;
//     t_env_export* curr_p1 = (*hold)->export_list;

//     while (curr_p1 != NULL && ft_strncmp(curr_p1->item, x_, 999) != 0) {
//         prev_p1 = curr_p1;
//         curr_p1 = curr_p1->next;
//     }
 
//     // Search for y (keep track of prevY and currY)
//     t_env_export* prev_p2 = NULL;
//     t_env_export* curr_p2 =(*hold)->export_list;
//     while (curr_p2 != NULL && ft_strncmp(curr_p2->item, i, 999) != 0) {
//         prev_p2 = curr_p2;
//         curr_p2 = curr_p2->next;
//     }
 
//     // If either x or y is not present, nothing to do
//     if (curr_p1 == NULL || curr_p2 == NULL)
//         return;
 
//     // If x is not the head of the linked list
//     if (prev_p1 != NULL)
//         prev_p1->next = curr_p2;
//     else // Else make y the new head
//         (*hold)->export_list = curr_p2;
 
//     // If y is not the head of the linked list
//     if (prev_p2 != NULL)
//         prev_p2->next = curr_p1;
//     else // Else make x the new head
//         (*hold)->export_list = curr_p1;
 
//     // Swap next pointers
//     t_env_export* tmp = curr_p2->next;
//     curr_p2->next = curr_p1->next;
//     curr_p1->next = tmp;
// //----------------------------------------------------
// }

void swap_nodes(t_hold **hold, char *x_, char *y_)
{
	t_env_export *prev_x = NULL;
	t_env_export *curr_x = (*hold)->export_list;
	t_env_export *prev_y = NULL;
	t_env_export *curr_y = (*hold)->export_list;
	// t_env_export *tmp = (*hold)->exportcurr__list;

	// search position for x
	while (curr_x != NULL && ft_strncmp(curr_x->var_name, x_, 999) != 0)
	{
		prev_x = curr_x;
		curr_x = curr_x->next;
	}
	// search position for y
	while (curr_y != NULL && ft_strncmp(curr_y->var_name, y_, 999) != 0)
	{
		prev_y = curr_y;
		curr_y = curr_y->next;
	}


//   If x is not the head of the linked list
    if (prev_x != NULL)
        prev_x->next = curr_y;
    else // Else make y the new head
        (*hold)->export_list = curr_y;
 
    // If y is not the head of the linked list
    if (prev_y != NULL)
        prev_y->next = curr_x;
    else // Else make x the new head
        (*hold)->export_list = curr_x;
 
    // Swap next pointers
    t_env_export* tmp = curr_y->next;
    curr_y->next = curr_x->next;
    curr_x->next = tmp;

}

void print_env(t_hold *hold)
{
	t_env_export *tmp = hold->export_list;
	while (tmp != NULL)
	{
		printf(RED"%s\n"RESET, tmp->item);
		tmp = tmp->next;
	}
}

// void sort_export_list(t_hold *hold)
// {
// 	// init var name and value in struct
// 	t_env_export *tmp;

// 	tmp = hold->export_list;
// 	while (tmp != NULL)
// 	{
// 		tmp->var_name = *(ft_split(tmp->item, '='));
// 		tmp->var_value = *(ft_split(tmp->item, '=') + 1);
// 		tmp = tmp->next;
// 	}
	
// 	t_env_export *x;
// 	t_env_export *y;

// 	x = hold->export_list;
// 	y = hold->export_list->next;
// 	while (x->next != NULL)
// 	{
// 		while (y->next != NULL)
// 		{
// 			if (ft_strncmp(x->var_name, y->var_name, ft_strlen(y->var_name)) == -1)		// means y is smoler
// 			{
// 				// printf(GRN"before: \n");
// 				// print_env(hold);
// 				swap_nodes(&hold, x->var_name, y->var_name);
// 				// printf(RED"after: \n\n");
// 				// print_env(hold);
// 				// printf(MAG"after: %s  >  %s\n"RESET, x->var_name, y->var_name);
// 			}
// 			y = y->next;
// 		}
// 		x = x->next;
// 		y = x->next;
// 	}

// 		tmp = hold->export_list;

// 		// adding 'declare -x' infront of everything
// 		while (tmp != NULL)
// 		{
// 			tmp->item = ft_strjoin("declare -x ", tmp->item);
// 			tmp = tmp->next;
// 		}

// 	t_env_export *print = hold->export_list;
// 		printf("print in sort func\n");
// 		while (print != NULL)
// 		{
// 			printf(CYN"%s\n"RESET, print->item);
// 			print = print->next;
// 		}
// }

void swap_data(t_env_export **export_list)
{
	// t_env_export *tmp = (*hold)->export_list;
	char	*tmp_item;
	char	*tmp_val;

	tmp_item = ft_strdup((*export_list)->item);
	tmp_val = ft_strdup((*export_list)->var_name);
	free((*export_list)->item);
	free((*export_list)->var_name);
	(*export_list)->item = ft_strdup((*export_list)->next->item);
	(*export_list)->var_name = ft_strdup((*export_list)->next->var_name);
	free((*export_list)->next->item);
	free((*export_list)->next->var_name);
	(*export_list)->next->item = ft_strdup(tmp_item);
	(*export_list)->next->var_name = ft_strdup(tmp_val);
	free(tmp_item);
	free(tmp_val);
}

void sort_export_list(t_env_export **export_list)
{
	t_env_export	*tmp;
	tmp = *export_list;
	while ((*export_list) != NULL && (*export_list)->next != NULL)
	{
printf(MAG"nefore check\n"RESET);
printf("var_name: %s\t\tnext var name: %s\n",(*export_list)->var_name, (*export_list)->next->var_name );
printf(MAG"after check\n"RESET);
		if (ft_strncmp((*export_list)->var_name, (*export_list)->next->var_name, 9) > 0)
		{
			swap_data((export_list));
			(*export_list) = tmp;
		}
		else
		{
printf("else statement\n");
			(*export_list) = (*export_list)->next;
		}
	}
	(*export_list) = tmp;
}

void create_env_export_list(t_hold *hold, char **ori_env)
{
	int32_t env_len = 0;
	t_env_export *head = hold->export_list;
	t_env_export *tmp_env;
	t_env_export *tmp_export;

	tmp_env = hold->env_list;
	tmp_export = hold->export_list;
	while (ori_env[env_len] != NULL)
	{
		// hold->env_list = add_node_env(hold, ori_env[env_len], "env");
		// hold->export_list = add_node_env(hold, ori_env[env_len], "export");
		tmp_env = add_node_env(hold, ori_env[env_len], "env");
		tmp_export = add_node_env(hold, ori_env[env_len], "export");
		env_len++;
	}
	print_env(hold);
	printf("before\n");
	hold->export_list = head;
	sort_export_list(&(hold->export_list));
	printf(GRN"after yeee\n"RESET);
	print_env(hold);
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



