#include "minishell.h"

void	env_builtin(t_hold *hold)
{
	t_env_export	*tmp;

	tmp = hold->env_list;
	while (tmp != NULL)
	{
		ft_putstr_fd(tmp->item, hold->parsed_list->outfile);
		write(2, "\n", 1);
		tmp = tmp->next;
	}
	free(tmp);
}

void	pwd_builtin(t_hold *hold)
{
	char	path[PATH_MAX];

	if (!getcwd(path, PATH_MAX))
	{
		exit_status(hold,
			RED"minishell: pwd: No such file or directory\n"RESET, 69);
		return ;
	}
	write(hold->parsed_list->outfile, path, ft_strlen(path));
	write(hold->parsed_list->outfile, "\n", 1);
}

bool	builtin(t_hold *hold, t_parsed_chunk *parsed_node)
{
	if (hold->lex_struct->macro == BUILTIN)
	{
		// printf(MAG"BUILTIN\n"RESET);
		if (ft_strncmp(hold->lex_struct->item, "echo", 4) == 0)
			return (echo_builtin(parsed_node), true);
		else if (ft_strncmp(hold->lex_struct->item, "env", 3) == 0)
			return (env_builtin(hold), true);
		else if (ft_strncmp(hold->lex_struct->item, "pwd", 3) == 0)
			return (pwd_builtin(hold), true);
		else if (ft_strncmp(hold->lex_struct->item, "cd", 2) == 0)
			return (cd_builtin(hold, parsed_node), true);
		else if (ft_strncmp(hold->lex_struct->item, "exit", 4) == 0)
			return (exit_builtin(hold, parsed_node), true);
		else if (ft_strncmp(hold->lex_struct->item, "unset", 5) == 0)
			return (unset_builtin(hold), true);
		// else if (ft_strncmp(hold->lex_struct->item, "export", 6) == 0)
		// 	return (export_builtin(hold), true);
		return (true);
	}
	else
		return (false);
}
