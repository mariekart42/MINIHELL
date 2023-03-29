#include "minishell.h"

void	sort_export_end(t_env_exp *export_list)
{
	t_env_exp	*tmp;

	tmp = export_list;
	while (export_list->next != NULL)
	{
		if (ft_strcmp(export_list->item, export_list->next->item) > 0)
		{
			swap_export(export_list);
			export_list = tmp;
		}
		export_list = export_list->next;
	}
}

void	add_to_export_mod(t_hold *hold, char *var_name, char *var_value,
							int var_class)
{
	t_env_exp	*new;
	t_env_exp	*tmp;
	char		*tmp_add;
	char		*tmp_add2;
	char		*tmp_add3;

	if (var_class == 1)
		tmp_add = ft_strjoin(var_name, "=\"\"");
	if (var_class == 2)
	{
		tmp_add3 = ft_strjoin(var_name, "=\"");
		tmp_add2 = ft_strjoin(tmp_add3, var_value);
		tmp_add = ft_strjoin(tmp_add2, "\"");
		free(tmp_add2);
		free(tmp_add3);
	}
	new = malloc(sizeof(t_env_exp));
	new->item = ft_strdup(tmp_add);
	free(tmp_add);
	new->next = NULL;
	tmp = hold->export_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	print_env_export(t_hold *hold)
{
	t_env_exp	*tmp;

	tmp = hold->export_list;
	while (tmp != NULL)
	{
		ft_putstr_fd("declare -x ", hold->pars_list->outfile);
		ft_putstr_fd(tmp->item, hold->pars_list->outfile);
		write(hold->pars_list->outfile, "\n", 1);
		tmp = tmp->next;
	}
}






int		export_empty(t_hold *hold, t_pars *parsed_node)
{
	if (parsed_node->args[1] == NULL)
	{
		print_env_export(hold);
		return (0);
	}
	return (1);
}

int		var_start_number(t_pars *parsed_node, int i)
{
	if (ft_isdigit(parsed_node->args[i][0]) != 0)
	{
		exit_status("export:", parsed_node->args[i],
			": not a valid identifier", 1);
		return (0);
	}
	return (1);
}

int	valid_value_export_var(t_pars *parsed_node, int i, int j)
{
	if (ft_isalnum_mod(parsed_node->args[i][j]) == 0)
	{
		exit_status("export:", parsed_node->args[i],
			": not a valid identifier", 1);
		return (0);
	}
	return (1);
}

void		var_class_zero(int var_class, t_hold *hold, t_pars *parsed_node,
							int i)
{
	if (var_class == 0)
	{
		find_var(hold, parsed_node->args[i], "export");
		add_to_env(hold, parsed_node->args[i], "export");
	}
}

void	non_zero_var(t_hold *hold, t_pars *parsed_node, int i, char *var_name)
{
	find_var(hold, var_name, "env");
	find_var(hold, var_name, "export");
	add_to_env(hold, parsed_node->args[i], "env");
}

void	export_builtin(t_hold *hold, t_pars *parsed_node)
{
	int		i;
	int		j;
	int		var_class;
	char	*var_name;
	char	*var_value;

	i = 1;
	if (export_empty(hold, parsed_node) == 0)
		return ;
	while (parsed_node->args[i] != NULL)
	{
		j = 0;
		if (var_start_number(parsed_node, i) == 0)
			return ;
		var_class = 0;
		while (parsed_node->args[i][j] != '\0')
		{
			if (valid_value_export_var(parsed_node, i, j) == 0)
				return ;
			if (parsed_node->args[i][j] == '=')
			{
				if (parsed_node->args[i][j + 1] == '\0')
					var_class = 1;
				if (parsed_node->args[i][j + 1] != '\0')
					var_class = 2;
				if (parsed_node->args[i][j + 1] != '\0')
					var_value = ft_strndup(&parsed_node->args[i][j + 1],
							ft_strlen(parsed_node->args[i]) + 1);
				var_name = ft_strndup(parsed_node->args[i], j);
				break ;
			}
			j++;
		}
		var_class_zero(var_class, hold, parsed_node, i);
		if (var_class != 0)
			non_zero_var(hold, parsed_node, i, var_name);
		if (var_class != 0)
			add_to_export_mod(hold, var_name, var_value, var_class);
		sort_export_end(hold->export_list);
		i++;
	}
}
