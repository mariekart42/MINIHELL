#include "minishell.h"

// Reference
// https://man7.org/linux/man-pages/man1/cd.1p.html
// https://man7.org/linux/man-pages/man3/chdir.3p.html

int	update_dir(t_hold *hold, char **args)
{
	char	*old;
	char	*new;
	t_env_export *tmp;

	old = NULL;
	old = getcwd(old, 0);
	if (chdir(args[1]) == -1)
	{
		free(old);
		return (-1);
	}
	new = NULL;
	new = getcwd(new, 0);
	// Use export_list instead of env_list
	tmp = hold->export_list;
	while (tmp != NULL)
	{
		// write(1, "Hiello!\n", 9);
		if (ft_strncmp(tmp->var_name, "PWD", 3) == 0)
			tmp->var_value = new;
		if (ft_strncmp(tmp->var_name, "OLDPWD", 6) == 0)
			tmp->var_value = old;
		tmp = tmp->next;
	}
	free(tmp);
	free(old);
	free(new);
	return (0);
}

void cd_builtin(t_hold *hold, t_parsed_chunk *parsed_node)
{
	char	*home;
	bool	is_home;
	t_env_export *tmp;
	
	if (parsed_node->args[1] == NULL)
	{
		is_home = true;
		// Use export_list instead of env_list
		tmp = hold->export_list;
		while (tmp != NULL)
		{
			// write(1, "Hiello!\n", 9);
			if (tmp->var_name)
			if (ft_strncmp(tmp->var_name, "HOME", 4) == 0)
				home = tmp->var_value;
			tmp = tmp->next;
		}
		free(tmp);
		if (home == NULL)
			is_home = false;
		if (is_home)
		{
			update_dir(hold, parsed_node->args);
			return ;
		}
		else
		{
			exit_status(hold, RED"minishell: cd: HOME not set\n"RESET, 69);
			return ;
		}
	}
	if (update_dir(hold, parsed_node->args) == -1)
	{
		ft_putstr_fd(RED"minshell: cd: ", 2);
		ft_putstr_fd(parsed_node->args[1], 2);
		exit_status(hold, ": No such file or directory\n"RESET, 69);
	}
	return ;
}
