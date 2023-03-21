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
}

void	pwd_builtin(t_hold *hold)
{
	char	path[PATH_MAX];

	if (!getcwd(path, PATH_MAX))
	{
		exit_status(RED"minishell: pwd: No such file or directory\n"RESET, 69);
		return ;
	}
	write(hold->parsed_list->outfile, path, ft_strlen(path));
	write(hold->parsed_list->outfile, "\n", 1);
}

void	builtin(t_hold *hold, t_parsed_chunk *parsed_node)
{
	if (hold->lex_struct->macro == BUILTIN)
	{
		if (ft_strncmp(hold->lex_struct->item, "echo", 4) == 0)
			echo_builtin(parsed_node);
		else if (ft_strncmp(hold->lex_struct->item, "env", 3) == 0)
			env_builtin(hold);
		else if (ft_strncmp(hold->lex_struct->item, "pwd", 3) == 0)
			pwd_builtin(hold);
		else if (ft_strncmp(hold->lex_struct->item, "cd", 2) == 0)
			cd_builtin(hold, parsed_node);
		else if (ft_strncmp(hold->lex_struct->item, "exit", 4) == 0)
			exit_builtin(parsed_node);
		else if (ft_strncmp(hold->lex_struct->item, "unset", 5) == 0)
			unset_builtin(hold, parsed_node);
		else if (ft_strncmp(hold->lex_struct->item, "export", 6) == 0)
			export_builtin(hold, parsed_node);
	}
}
