#include "minishell.h"

/* bash:	If the current working directory is a symbolic link that points to a 
 * 			directory that no longer exists, the pwd command will fail with a 
 * 			"No such file or directory" error								*/
void pwd_builtin(t_hold *hold)
{
	char	path[PATH_MAX];
	
	if (!getcwd(path, PATH_MAX))
	{
		exit_status(hold, RED"PWD: NO SUCH FILE OR DIRECTORY\n"RESET, 69);
		return ;
	}
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
}

bool echo_builtin_helper(t_hold *hold, int i, bool is_nflag) 
{
	char	**args;
	int32_t	outfile;
	int		j;

	args = hold->parsed_list->args;
	outfile = hold->parsed_list->outfile;
	j = 1;
	if (ft_strncmp(args[i], "-n", 2) == 0)
	{
		while (args[i][j] != NULL)
		{
			if (args[i][j] == "n")
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
	if (!is_nflag)
		ft_putstr_fd(args[i], outfile);
	return (is_nflag);
}

// Need to add option of -n
// Remove new line from the print out
void echo_builtin(t_hold *hold)
{
	char	**args;
	int		i;
	bool	is_nflag;

	args = hold->parsed_list->args;
	i = 1;
	is_nflag = false;
	// echo alone print new line
	if (args[1] = NULL)
	{
		ft_putstr_fd("\n", 1);
		// exit with (0)
		// return (0);
		return ;
	}
	
	// -n -n -n loop
	while (args[i] != NULL)
	{
		is_nflag = echo_builtin_helper(hold, i, is_nflag);
		i++;
		if (!is_nflag)
			break ;
	}

	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], hold->parsed_list->outfile);
		if (args[i + 1] == NULL)
			break ;
		ft_putstr_fd(" ", hold->parsed_list->outfile);
		i++;
	}

	if (!is_nflag)
		ft_putstr_fd("\n", 1);
	// exit with (0)
	// return (0);
	return ;
}

void env_builtin(t_hold *hold)
{
	t_env_export *tmp;
	
	tmp = hold->env_list;
	while (tmp != NULL)
	{
		ft_putstr_fd(tmp->item, 2);
		write(2, "\n", 1);
		tmp = tmp->next;
	}
}




void cd_builtin(t_hold *hold)
{
	if (hold->lex_struct->next->item == NULL)
	{
		printf(RED"adding homedirectory feature later!\nEXIT\n"RESET);
		exit(0);
	}
	// get $HOME from own env list and give it to chrir as an argument
	
	if (chdir(hold->lex_struct->next->item) < 0)
	{
		ft_putstr_fd(RED"", 2); //just for making it red lol
		write(1, hold->lex_struct->next->item, ft_strlen(hold->lex_struct->next->item));
		exit_status(hold, ": NO SUCH FILE OR DIRECTORY\n"RESET, 69);
		return ;
	}

}


// void unset_builtin(t_hold *hold)
// {

// }
// void echo_builtin(t_hold *hold)
// {

// }
// void exit_builtin(t_hold *hold)
// {

// }

bool builtin(t_hold *hold)
{
	if (hold->lex_struct->macro == BUILTIN)
	{
		// printf(MAG"BUILTIN\n"RESET);
		if (ft_strncmp(hold->lex_struct->item, "env", 3) == 0)
			return (env_builtin(hold), true);
		// else if (ft_strncmp(hold->lex_struct->item, "export", 6) == 0)
		// 	return (export_builtin(hold), true);
		// else if (ft_strncmp(hold->lex_struct->item, "pwd", 3) == 0)
		// 	return (pwd_builtin(hold), true);
		// else if (ft_strncmp(hold->lex_struct->item, "cd", 2) == 0)
		// 	return (cd_builtin(hold), true);
		// else if (ft_strncmp(hold->lex_struct->item, "unset", 5) == 0)
		// 	return (unset_builtin(hold), true);
		else if (ft_strncmp(hold->lex_struct->item, "echo", 4) == 0)
			return (echo_builtin(hold), true);
		// else if (ft_strncmp(hold->lex_struct->item, "exit", 4) == 0)
		// 	return (exit_builtin(hold), true);
		return (true);
	}
	else
		return (false);
}