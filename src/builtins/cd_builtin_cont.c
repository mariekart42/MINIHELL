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

void	add_to_export_cd(t_hold *hold, char *var_name, char *var_value,
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
