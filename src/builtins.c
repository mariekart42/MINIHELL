#include "minishell.h"

void	env_builtin(t_hold *hold, t_parsed_chunk *parsed_node)
{
	t_env_export	*tmp;
	char			**args;
	int				i;

	args = parsed_node->args;
	i = 1;
	while (args[i] != NULL)
	{
		if (ft_strncmp(args[i], "env", 3) != 0)
		{
			// ft_putstr_fd(RED"minishell: env: ", 2);
			// ft_putstr_fd(args[i], 2);
			exit_status("env:", args[i], ": No such file or directory", 127);
			return ;
		}
		i++;
	}
	tmp = hold->env_list;
	while (tmp != NULL)
	{
		ft_putstr_fd(tmp->item, hold->parsed_list->outfile);
		write(2, "\n", 1);
		tmp = tmp->next;
	}
}

void	pwd_builtin(t_hold *hold, t_parsed_chunk *parsed_node)
{
	char	path[PATH_MAX];

	if (!getcwd(path, PATH_MAX))
	{
		exit_status("pwd: No such file or directory", "", "", 127);
		return ;
	}
	if (parsed_node->args[1] == NULL
		|| ft_strncmp(&parsed_node->args[1][0], "-", 1) != 0)
	{
		write(hold->parsed_list->outfile, path, ft_strlen(path));
		write(hold->parsed_list->outfile, "\n", 1);
		return ;
	}
	if (ft_strncmp(&parsed_node->args[1][0], "-", 1) == 0)
	{
		// ft_putstr_fd(RED"minishell: pwd: ", 2);
		// ft_putstr_fd(parsed_node->args[1], 2);
		exit_status("pwd:", parsed_node->args[1], ": invalid option", 2);
		return ;
	}
}

bool	builtin(t_hold *hold, t_parsed_chunk *parsed_node)
{
	// error_code = 0;
	if (ft_strncmp(parsed_node->args[0], "echo", 4) == 0)
		return (echo_builtin(hold, parsed_node), true);
	else if (ft_strncmp(parsed_node->args[0], "env", 3) == 0)
		return (env_builtin(hold, parsed_node), true);
	else if (ft_strncmp(parsed_node->args[0], "pwd", 3) == 0)
		return (pwd_builtin(hold, parsed_node), true);
	else if (ft_strncmp(parsed_node->args[0], "cd", 2) == 0)
		return (cd_builtin(hold, parsed_node), true);
	else if (ft_strncmp(parsed_node->args[0], "exit", 4) == 0)
		return (exit_builtin(hold, parsed_node), true);
	else if (ft_strncmp(parsed_node->args[0], "unset", 5) == 0)
		return (unset_builtin(hold, parsed_node), true);
	else if (ft_strncmp(parsed_node->args[0], "export", 6) == 0)
		return (export_builtin(hold, parsed_node), true);
	return (false);
}
