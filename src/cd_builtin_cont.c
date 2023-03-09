#include "minishell.h"

void	add_to_env(t_hold *hold, char *add, char *structure)
{
	t_env_export	*new;
	t_env_export	*tmp;

	new = malloc(sizeof(t_env_export));
	new->item = ft_strdup(add);
	new->next = NULL;
	if (ft_strncmp(structure, "env", 3) == 0)
		tmp = hold->env_list;
	if (ft_strncmp(structure, "export", 6) == 0)
		tmp = hold->export_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	update_env(t_hold *hold, char *old, char *new, char *structure)
{
	t_env_export	*tmp;
	char			*tmp2;
	char			*tmp3;
	bool			is_oldpwd;

	is_oldpwd = false;
	tmp2 = ft_strjoin("OLDPWD=", old);
	tmp3 = ft_strjoin("PWD=", new);
	if (ft_strncmp(structure, "env", 3) == 0)
		tmp = hold->env_list;
	if (ft_strncmp(structure, "export", 6) == 0)
		tmp = hold->export_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->item, "PWD", 3) == 0)
			tmp->item = tmp3;
		if (ft_strncmp(tmp->item, "OLDPWD", 6) == 0)
		{
			tmp->item = tmp2;
			is_oldpwd = true;
		}
		tmp = tmp->next;
	}
	if (!is_oldpwd)
		add_to_env(hold, old, structure);
	free(tmp2);
	free(tmp3);
}

void	add_to_var(t_hold *hold, char *add, char *structure)
{
	t_env_export	*new;
	t_env_export	*tmp;

	new = NULL;
	new->var_name = "OLDPWD=";
	new->var_value = add;
	if (ft_strncmp(structure, "env", 3) == 0)
		tmp = hold->env_list;
	if (ft_strncmp(structure, "export", 6) == 0)
		tmp = hold->export_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	update_var_value(t_hold *hold, char *old, char *new, char *structure)
{
	t_env_export	*tmp;
	bool			is_oldpwd;

	is_oldpwd = false;
	if (ft_strncmp(structure, "env", 3) == 0)
		tmp = hold->env_list;
	if (ft_strncmp(structure, "export", 6) == 0)
		tmp = hold->export_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->item, "PWD", 3) == 0)
			tmp->var_value = new;
		if (ft_strncmp(tmp->item, "OLDPWD", 6) == 0)
		{
			tmp->var_value = old;
			is_oldpwd = true;
		}
		tmp = tmp->next;
	}
	if (!is_oldpwd)
		add_to_var(hold, old, structure);
}
