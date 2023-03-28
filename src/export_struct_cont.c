#include "minishell.h"

void	swap_data(t_env_exp *export_list)
{
	char	*tmp_item;
	char	*tmp_value;
	char	*tmp_name;

	tmp_name = ft_strdup(export_list->var_name);
	tmp_item = export_list->item;
	tmp_value = ft_strdup(export_list->var_value);
	free(export_list->var_name);
	free(export_list->var_value);
	export_list->var_name = ft_strdup(export_list->next->var_name);
	export_list->item = export_list->next->item;
	export_list->var_value = ft_strdup(export_list->next->var_value);
	free(export_list->next->var_name);
	free(export_list->next->var_value);
	export_list->next->var_name = tmp_name;
	export_list->next->item = tmp_item;
	export_list->next->var_value = tmp_value;
}
