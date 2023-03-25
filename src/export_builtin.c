#include "minishell.h"

void	swap_export(t_env_export *export_list)
{
	char	*tmp;

	tmp = export_list->item;
	export_list->item = export_list->next->item;
	export_list->next->item = tmp;
}


void	sort_export_end(t_env_export *export_list) 
{
	t_env_export *tmp;

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

void	add_to_export_mod(t_hold *hold, char *var_name, char *var_value, int var_class)
{
	t_env_export	*new;
	t_env_export	*tmp;
	char			*tmp_add;
	char			*tmp_add2;
	char			*tmp_add3;

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
	new = malloc(sizeof(t_env_export));
	new->item = ft_strdup(tmp_add);
	free(tmp_add);
	new->next = NULL;
	tmp = hold->export_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void print_env_export(t_hold *hold)
{
	t_env_export *tmp;
	
	tmp = hold->export_list;
	while (tmp != NULL)
	{
		ft_putstr_fd("declare -x ", hold->parsed_list->outfile);
		ft_putstr_fd(tmp->item, hold->parsed_list->outfile);
		write(hold->parsed_list->outfile, "\n", 1);
		tmp = tmp->next;
	}
}

int		ft_isalnum_mod(int val)
{
	if ((val >= 48 && val <= 57) || (val >= 65 && val <= 90) || \
		(val >= 97 && val <= 122) || val == 61 || val == 95)
		return (1);
	return (0);
}

void	export_builtin(t_hold *hold, t_parsed_chunk *parsed_node)
{
	int		i;
	int		j;
	int		var_class;
	char	*var_name;
	char	*var_value;

	i = 1;
	j = 0;
	if (parsed_node->args[1] == NULL)
	{
		print_env_export(hold);
		return ;
	}
	while (parsed_node->args[i] != NULL)
	{
		var_class = 0;
		while (parsed_node->args[i][j] != '\0')
		{
			if (ft_isalnum_mod(parsed_node->args[i][j]) == 0)
			{
				ft_putstr_fd(RED"minshell: export: ", 2);
				ft_putstr_fd(parsed_node->args[i], 2);
				exit_status(": not a valid identifier\n"RESET, 1);
				return ;
			}
			if (parsed_node->args[i][j] == '=')
			{
				if (parsed_node->args[i][j + 1] == '\0')
					var_class = 1;
				else
				{
					var_class = 2;
					var_value = ft_strndup(&parsed_node->args[i][j + 1], ft_strlen(parsed_node->args[i]) + 1);
				}
				var_name = ft_strndup(parsed_node->args[i], j);
				break ;
			}
			j++;
		}
		if (var_class == 0)
		{
			find_var(hold, parsed_node->args[i], "export");
			add_to_env(hold, parsed_node->args[i], "export");
		}
		else
		{
			find_var(hold, var_name, "env");
			find_var(hold, var_name, "export");
			add_to_env(hold, parsed_node->args[i], "env");
			add_to_export_mod(hold, var_name, var_value, var_class);
		}
		sort_export_end(hold->export_list);
		j = 0;
		i++;
	}
}
