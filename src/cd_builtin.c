#include "minishell.h"

// Reference
// https://man7.org/linux/man-pages/man1/cd.1p.html
// https://man7.org/linux/man-pages/man3/chdir.3p.html

int	update_dir(t_hold *hold, t_parsed_chunk *parsed_node)
{

	return (0);
}

//


void cd_builtin(t_hold *hold, t_parsed_chunk *parsed_node)
{
	char	*home;
	bool	is_home;
	char	**args;
	t_env_export *tmp;
	
	is_home = true;
	args = parsed_node->args;
	tmp = hold->env_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var_name, "HOME", 4) == 0)
			home = tmp->var_value;
		tmp = tmp->next;
	}
	free(tmp);
	if (home == NULL)
		is_home = false;
	
	if (args[1] == NULL)
	{
		if (is_home)
			// Change to HOME
			return ;
		else
		{
			exit_status(hold, RED"minishell: cd: HOME not set\n"RESET, 69);
			return ;
		}
	}
	if (ft_strncmp(args[1], ".", 2))
		return ;
	if (ft_strncmp(args[1], "..", 2))
	{
		// Go one level up
		// Handle in update_dir?
		return ;
	}
	if (update_dir(hold, parsed_node) == -1)
	{
		ft_putstr_fd(RED"minshell: cd: ", 2);
		ft_putstr_fd(args[1], 2);
		exit_status(hold, ": No such file or directory\n"RESET, 69);
	}
	return ;
}

// cd / -> / (Absolute directory)
// cd or cd ~ -> HOME