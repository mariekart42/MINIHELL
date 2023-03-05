#include "minishell.h"

void	update_env(t_hold *hold, char *old, char *new, char *structure)
{
	t_env_export	*tmp;
	bool			is_oldpwd;

	is_oldpwd = false;
	old = ft_strjoin("OLDPWD=", old);
	new = ft_strjoin("PWD=", new);
	if (ft_strncmp(structure, "env", 3) == 0)
		tmp = hold->env_list;
	if (ft_strncmp(structure, "export", 6) == 0)
		tmp = hold->export_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->item, "PWD", 3) == 0)
			tmp->item = new;
		if (ft_strncmp(tmp->item, "OLDPWD", 6) == 0)
		{
			tmp->item = old;
			is_oldpwd = true;
		}
		tmp = tmp->next;
	}
	if (!is_oldpwd)
		add_to_env(hold, old);
	free(tmp);
}

void	free_vars(t_env_export *tmp, char *old, char *new)
{
	free(tmp);
	free(old);
	free(new);
}

int	update_dir(t_hold *hold, char **args)
{
	char			*old;
	char			*new;
	t_env_export	*tmp;

	old = NULL;
	old = getcwd(old, 0);
	if (chdir(args[1]) == -1)
	{
		free(old);
		return (-1);
	}
	new = NULL;
	new = getcwd(new, 0);
	tmp = hold->export_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var_name, "PWD", 3) == 0) // Change item
			tmp->var_value = new;
		if (ft_strncmp(tmp->var_name, "OLDPWD", 6) == 0)
			tmp->var_value = old;
		tmp = tmp->next;
	}
	update_env(hold, old, new, "env");
	update_env(hold, old, new, "export");
	free_vars(tmp, old, new);
	return (0);
}

void	change_to_home(t_hold *hold)
{
	bool			is_home;
	t_env_export	*tmp;
	char			*home;
	char			*args[2];

	is_home = true;
	tmp = hold->export_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var_name, "HOME", 4) == 0)
			home = tmp->var_value;
		tmp = tmp->next;
	}
	free(tmp);
	if (home == NULL)
		is_home = false;
	if (is_home)
	{
		args[0] = NULL;
		args[1] = home;
		update_dir(hold, args);
	}
	else
		exit_status(hold, RED"minishell: cd: HOME not set\n"RESET, 69);
}

void	cd_builtin(t_hold *hold, t_parsed_chunk *parsed_node)
{
	if (parsed_node->args[1] == NULL)
	{
		change_to_home(hold);
		return ;
	}
	if (update_dir(hold, parsed_node->args) == -1)
	{
		ft_putstr_fd(RED"minshell: cd: ", 2);
		ft_putstr_fd(parsed_node->args[1], 2);
		exit_status(hold, ": No such file or directory\n"RESET, 69);
	}
	return ;
}
