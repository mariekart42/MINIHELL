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
	if (parsed_node->args[1] == NULL)
		print_env_export(hold);
	//while (args)
		// if var
		// if var=
		// if var=value

	// Modify env and export in both cases
}