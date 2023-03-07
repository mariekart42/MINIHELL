#include "minishell.h"

void export_builtin(t_hold *hold)
{
	t_env_export *tmp;
	
	tmp = hold->export_list;
	while (tmp != NULL)
	{
		ft_putstr_fd(tmp->item, hold->parsed_list->outfile);
		write(2, "\n", 1);
		tmp = tmp->next;
	}
}
