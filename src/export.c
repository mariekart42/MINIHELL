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
	char	*tmp_value;
	char	*tmp_name;

	tmp_name = ft_strdup(export_list->var_name);
	tmp_item = export_list->item;
	tmp_value = ft_strdup(export_list->var_value);
		free(export_list->var_name); 
		free(export_list->var_value); 
		// free(export_list->item); 

	export_list->var_name = ft_strdup(export_list->next->var_name);
	export_list->item = export_list->next->item;
	export_list->var_value = ft_strdup(export_list->next->var_value);
	free(export_list->next->var_name);
	free(export_list->next->var_value);
	// free(export_list->next->item);

	export_list->next->var_name = tmp_name;
	export_list->next->item = tmp_item;
	export_list->next->var_value = tmp_value;
	// free(tmp_item);
	// free(tmp_name);
	// free(tmp_value);
}

void sort_export_list(t_hold *hold)
{
	// init var name and value in struct
	t_env_export *tmp;
	char **tmp_tmp;

	int i = 2;
	tmp = hold->export_list;
	while (tmp != NULL)
	{
		tmp_tmp = ft_split(tmp->item, '=');
		tmp->var_name = tmp_tmp[0];
		tmp->var_value = tmp_tmp[1];
		while (tmp_tmp[i] != NULL)
		{
			tmp->var_value = ft_strjoin(tmp->var_value, tmp_tmp[i]);
			i++;
		}
		free(tmp_tmp);
		i = 2;
		tmp = tmp->next;
	}

	tmp = hold->export_list;
	while (hold->export_list != NULL && hold->export_list->next != NULL)
	{
		if (ft_strncmp(hold->export_list->var_name, hold->export_list->next->var_name, ft_strlen(hold->export_list->next->var_name)) > 0)
		{
			swap_data(hold->export_list);
			hold->export_list = tmp;
		}
		else
			hold->export_list = hold->export_list->next;
	}
	hold->export_list = tmp;
}
