#include "minishell.h"

void	var_class_zero(int var_class, t_hold *hold, t_pars *parsed_node,
							int i)
{
	if (var_class == 0)
	{
		find_var(hold, parsed_node->args[i], "export");
		add_to_env(hold, parsed_node->args[i], "export");
	}
}

void	var_class_non_zero(t_hold *hold, t_pars *parsed_node, int i[],
			char **vars)
{
	if (i[2] != 0)
	{
		non_zero_var(hold, parsed_node, i[0], vars[0]);
		add_to_export_mod(hold, vars, i[2]);
	}
}

void	non_zero_var(t_hold *hold, t_pars *parsed_node, int i, char *var_name)
{
	find_var(hold, var_name, "env");
	find_var(hold, var_name, "export");
	add_to_env(hold, parsed_node->args[i], "env");
}

void	sort_export_end(t_env_exp *export_list)
{
	t_env_exp	*tmp;

	tmp = export_list;
	while (export_list && export_list->next != NULL)
	{
		if (ft_strcmp(export_list->item, export_list->next->item) > 0)
		{
			swap_export(export_list);
			export_list = tmp;
		}
		export_list = export_list->next;
	}
}

void	swap_export(t_env_exp *export_list)
{
	char	*tmp;

	tmp = export_list->item;
	export_list->item = export_list->next->item;
	export_list->next->item = tmp;
}
