#include "minishell.h"

void export_builtin(t_hold *hold)
{
	t_env_export *tmp;
	
	tmp = hold->export_list;
	while (tmp != NULL)
	{
		ft_putstr_fd(tmp->item, 2);
		write(2, "\n", 1);
		tmp = tmp->next;
	}
}

void swap_data(t_env_export *export_list)
{
	char	*tmp_item;
	char	*tmp_val;

	tmp_item = ft_strdup(export_list->item);
	tmp_val = ft_strdup(export_list->var_name);
	free(export_list->var_name); 
	export_list->item = ft_strdup(export_list->next->item);
	export_list->var_name = ft_strdup(export_list->next->var_name);
	free(export_list->next->var_name);
	export_list->next->item = ft_strdup(tmp_item);
	export_list->next->var_name = ft_strdup(tmp_val);
	free(tmp_item);
	free(tmp_val);
}

void sort_export_list(t_hold *hold)
{
	// init var name and value in struct
	t_env_export *tmp;
	char **tmp_tmp;

	tmp = hold->export_list;
	while (tmp != NULL)
	{
		tmp_tmp = ft_split(tmp->item, '=');
		tmp->var_name = tmp_tmp[0];
		int i = 1;
		while (tmp_tmp[i] != NULL)
		{
			free(tmp_tmp[i]);
			i++;
		}
		free(tmp_tmp);
		i = 0;
		// tmp->var_name = *(ft_split(tmp->item, '='));

// next do same with var_value

		// tmp->var_value = *(ft_split(tmp->item, '=') + 1);
		tmp = tmp->next;
	}
	// tmp = hold->export_list;
	// while (hold->export_list != NULL && hold->export_list->next != NULL)
	// {
	// 	if (ft_strncmp(hold->export_list->var_name, hold->export_list->next->var_name, ft_strlen(hold->export_list->next->var_name)) > 0)
	// 	{
	// 		swap_data(hold->export_list);
	// 		hold->export_list = tmp;
	// 	}
	// 	else
	// 		hold->export_list = hold->export_list->next;
	// }
	// hold->export_list = tmp;
}
