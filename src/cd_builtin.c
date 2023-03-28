#include "minishell.h"

char	*create_path_var(char *var_name, char *var_value)
{
	char			*tmp_add;
	char			*tmp_add2;

	tmp_add2 = ft_strjoin(var_name, "=");
	tmp_add = ft_strjoin(tmp_add2, var_value);
	free(tmp_add2);
	return (tmp_add);
}

void	update_dir_cont(t_hold *hold, char *new, char *old)
{
	char	*pwd;
	char	*oldpwd;

	pwd = create_path_var("PWD", new);
	oldpwd = create_path_var("OLDPWD", old);
	find_var(hold, "PWD", "env");
	find_var(hold, "OLDPWD", "env");
	add_to_env(hold, pwd, "env");
	add_to_env(hold, oldpwd, "env");
	find_var(hold, "PWD", "export");
	find_var(hold, "OLDPWD", "export");
	add_to_export_mod(hold, "PWD", new, 2);
	add_to_export_mod(hold, "OLDPWD", old, 2);
	sort_export_end(hold->export_list);
	free(pwd);
	free(oldpwd);
}

int	update_dir(t_hold *hold, char **args)
{
	char			*old;
	char			*new;

	old = NULL;
	old = getcwd(old, 0);
	if (chdir(args[1]) == -1)
	{
		free(old);
		return (-1);
	}
	new = NULL;
	new = getcwd(new, 0);
	update_dir_cont(hold, new, old);
	free(old);
	free(new);
	return (0);
}

void	change_to_home(t_hold *hold)
{
	bool			is_home;
	t_env_exp	*tmp;
	char			*home;
	char			*args[2];

	is_home = true;
	home = NULL;
	tmp = hold->export_list;
	while (tmp != NULL && tmp->item)
	{
		if (ft_strncmp(tmp->item, "HOME", 4) == 0)
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
		exit_status("cd: HOME not set", "", "", 1);
}

void	cd_builtin(t_hold *hold, t_pars *parsed_node)
{
	char	**args;

	args = parsed_node->args;
	if (args[1] == NULL || ft_strncmp(args[0], "cd~", 3) == 0
		|| args[1][0] == '~')
	{
		change_to_home(hold);
		return ;
	}
	if (args[2])
	{
		// ft_putstr_fd(RED"minshell: cd: ", 2);
		// ft_putstr_fd(args[1], 2);
		exit_status("cd:", args[1], ": too many arguments", 1);
		return ;
	}
	if (update_dir(hold, args) == -1)
	{
		// ft_putstr_fd(RED"minshell: cd: ", 2);
		// ft_putstr_fd(args[1], 2);
		exit_status("cd:", args[1], ": No such file or directory", 1);
	}
	return ;
}
