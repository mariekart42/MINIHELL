#include "minishell.h"

void	update_dir_cont(t_hold *hold, char *old, char *new)
{
	update_var_value(hold, old, new, "export");
	update_env(hold, old, new, "env");
	update_env(hold, old, new, "export");
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
		if (ft_strncmp(tmp->var_name, "PWD", 3) == 0)
			tmp->var_value = new;
		if (ft_strncmp(tmp->var_name, "OLDPWD", 6) == 0)
			tmp->var_value = old;
		tmp = tmp->next;
	}
	update_dir_cont(hold, old, new);
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
	if (home == NULL)
		is_home = false;
	if (is_home)
	{
		args[0] = NULL;
		args[1] = home;
		update_dir(hold, args);
	}
	else
		exit_status(RED"minishell: cd: HOME not set\n"RESET, 69);
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
		exit_status(": No such file or directory\n"RESET, 69);
	}
	return ;
}
