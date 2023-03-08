#include "minishell.h"

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

void export_builtin(t_hold *hold, t_parsed_chunk *parsed_node)
{
	int		i;
	int		j;
	int		var_class;
	char	*tmp_args;

	i = 1;
	j = 0;
	if (parsed_node->args[1] == NULL)
		print_env_export(hold);

	while (parsed_node->args[i] != NULL)
	{
		var_class = 0;
		while (parsed_node->args[i][j] != '\0')
		{
			if (parsed_node->args[i][j] == '=')
			{
				if (parsed_node->args[i][j + 1] == '\0')
					var_class = 1;
				else
					var_class = 2;
			}
			j++;
		}
		if (var_class == 0)
		{
			add_to_env(hold, parsed_node->args[i], "env");
			add_to_env(hold, parsed_node->args[i], "export");
			// sort_export_list(hold); // Problem for Future Santiago
		}
		if (var_class == 1)
		{
			tmp_args = ft_strjoin(parsed_node->args[i], "");
			add_to_env(hold, tmp_args, "env");
			add_to_env(hold, tmp_args, "export");
			// sort_export_list(hold); // Problem for Future Santiago
			free(tmp_args);
		}
		if (var_class == 2)
		{
			add_to_env(hold, parsed_node->args[i], "env");
			add_to_env(hold, parsed_node->args[i], "export");
			// sort_export_list(hold); // Problem for Future Santiago
		}
		j = 0;
		i++;
	}

	// Check with "string cases"
	// Modify env and export in both cases
}