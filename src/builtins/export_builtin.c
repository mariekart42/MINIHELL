#include "minishell.h"

int	is_equal_sign(t_pars *parsed_node, int i[], char**vars)
{
	int		var_class;

	var_class = 0;
	if (parsed_node->args[i[0]][i[1]] == '=')
	{
		var_class = get_var_type(parsed_node, i[0], i[1]);
		if (var_class == 2)
			vars[1] = assign_var_value(parsed_node, i[0], i[1]);
		vars[0] = ft_strndup(parsed_node->args[i[0]], i[1]);
	}
	return (var_class);
}

int	not_valid_value_export_var(t_pars *parsed_node, int i, int j)
{
	if (ft_isalnum_mod(parsed_node->args[i][j]) == 0)
	{
		exit_status("export:", parsed_node->args[i],
			": not a valid identifier", 1);
		return (1);
	}
	return (1);
}

void	export_not_empty_helper(int i[], t_hold *hold,
			t_pars *parsed_node, char *vars[2])
{
	var_class_zero(i[2], hold, parsed_node, i[0]);
	var_class_non_zero(hold, parsed_node, i, vars);
	if (vars[0])
		free(vars[0]);
	if (vars[1])
		free(vars[1]);
}

void	export_not_empty(t_hold *hold, t_pars *parsed_node)
{
	char	*vars[2];
	int		i[3];

	i[0] = 1;
	vars[0] = NULL;
	vars[1] = NULL;
	while (parsed_node->args[i[0]] != NULL)
	{
		i[1] = 0;
		if (var_start_number(parsed_node, i[0]) == 0)
			return ;
		i[2] = 0;
		while (parsed_node->args[i[0]][i[1]] != '\0')
		{
			if (not_valid_value_export_var(parsed_node, i[0], i[1]) == 0)
				return ;
			i[2] = is_equal_sign(parsed_node, i, vars);
			if (i[2] != 0)
				break ;
			i[1]++;
		}
		export_not_empty_helper(i, hold, parsed_node, vars);
		sort_export_end(hold->export_list);
		i[0]++;
	}
}

void	export_builtin(t_hold *hold, t_pars *parsed_node)
{
	if (export_empty(hold, parsed_node) == 0)
		return ;
	export_not_empty(hold, parsed_node);
}
