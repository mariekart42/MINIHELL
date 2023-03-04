#include "minishell.h"

void	add_to_env(t_hold *hold, char *add)
{
	t_env_export	*new;
	t_env_export	*tmp;

	new = NULL;
	new->item = add;
	tmp = hold->env_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
	free(tmp);
}
