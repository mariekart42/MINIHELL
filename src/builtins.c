#include "minishell.h"

bool echo_builtin_helper(t_parsed_chunk *parsed_node, int i, bool is_nflag) 
{
	char	**args;
	int32_t	outfile;
	int		j;

	args = parsed_node->args;
	outfile = parsed_node->outfile;
	j = 1;
	is_nflag = false;
	if (ft_strncmp(args[i], "-n", 2) == 0)
	{
		while (args[i][j] != '\0')
		{
			if (args[i][j] == 'n')
			{
				j++;
				is_nflag = true;
			}
			else
			{
				is_nflag = false;
				break ;
			}
		}
	}
	return (is_nflag);
}

void echo_builtin(t_parsed_chunk *parsed_node)
{
	char	**args;
	int		i;
	bool	is_nflag;
	bool 	temp_flag;

	args = parsed_node->args;
	i = 1;
	is_nflag = false;
	if (args[1] == NULL)
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	while (args[i] != NULL)
	{
		temp_flag = echo_builtin_helper(parsed_node, i, is_nflag);
		if (!temp_flag)
			break ;
		is_nflag = temp_flag;
		i++;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], parsed_node->outfile);
		if (args[i + 1] != NULL)
			ft_putstr_fd(" ", parsed_node->outfile);
		i++;
	}
	if (!is_nflag)
		ft_putstr_fd("\n", 1);
	return ;
}

void env_builtin(t_hold *hold)
{
	t_env_export *tmp;
	
	tmp = hold->env_list;
	while (tmp != NULL)
	{
		ft_putstr_fd(tmp->item, hold->parsed_list->outfile);
		write(2, "\n", 1);
		tmp = tmp->next;
	}
	free(tmp);
}

void pwd_builtin(t_hold *hold)
{
	char	path[PATH_MAX];
	
	if (!getcwd(path, PATH_MAX))
	{
		exit_status(hold, RED"minishell: pwd: No such file or directory\n"RESET, 69);
		return ;
	}
	write(hold->parsed_list->outfile, path, ft_strlen(path));
	write(hold->parsed_list->outfile, "\n", 1);
}


bool builtin(t_hold *hold, t_parsed_chunk *parsed_node)
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
		// else if (ft_strncmp(hold->lex_struct->item, "exit", 4) == 0)
		// 	return (exit_builtin(hold), true);
		// else if (ft_strncmp(hold->lex_struct->item, "export", 6) == 0)
		// 	return (export_builtin(hold), true);
		// else if (ft_strncmp(hold->lex_struct->item, "unset", 5) == 0)
		// 	return (unset_builtin(hold), true);
		return (true);
	}
	else
		return (false);
}