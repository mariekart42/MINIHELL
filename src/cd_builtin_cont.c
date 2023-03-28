#include "minishell.h"

void	add_to_env(t_hold *hold, char *add, char *structure)
{
	t_env_exp	*new;
	t_env_exp	*tmp;

	new = malloc(sizeof(t_env_exp));
	new->item = ft_strdup(add);
	new->next = NULL;
	tmp = NULL;
	if (ft_strncmp(structure, "env", 3) == 0)
		tmp = hold->env_list;
	if (ft_strncmp(structure, "export", 6) == 0)
		tmp = hold->export_list;
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
