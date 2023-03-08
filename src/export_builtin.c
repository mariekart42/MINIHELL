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
	int	i;
	int	j;
	int	var_class;

	i = 0;
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

		// if var_class == 2
			// ft_strjoin remaining args
			// function(parsed_node->args[i])
			// return

		// if var_class = 1
			// ft_strjoin ""
			// function(parsed_node->args[i]);

		// if var_class = 0
			//function(parsed_node->args[i]);
		j = 0;
		i++;
	}

	// Modify env and export in both cases
}