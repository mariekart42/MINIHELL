#include "minishell.h"

bool	echo_builtin_helper(t_pars *parsed_node, int i, bool is_nflag)
{
	char	**args;
	int		j;

	args = parsed_node->args;
	j = 1;
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

void	echo_builtin_cont(t_pars *parsed_node, int *i, bool is_nflag)
{
	char	**args;

	args = parsed_node->args;
	while (args[*i] != NULL)
	{
		ft_putstr_fd(args[*i], 1);
		if (args[*i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		(*i)++;
	}
	if (!is_nflag)
		ft_putstr_fd("\n", 1);
}

bool	is_nflag_func(char **args, t_pars *parsed_node, int *i)
{
	bool	temp_flag;
	bool	is_nflag;

	is_nflag = false;
	while (args[*i] != NULL)
	{
		temp_flag = echo_builtin_helper(parsed_node, *i, is_nflag);
		if (!temp_flag)
			break ;
		is_nflag = temp_flag;
		(*i)++;
	}
	return (is_nflag);
}

void	echo_builtin(t_hold *hold, t_pars *parsed_node)
{
	(void)hold;
	char			**args;
	int				i;
	bool			is_nflag;

	args = parsed_node->args;
	i = 1;
	is_nflag = false;
	if (args[1] == NULL)
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	is_nflag = is_nflag_func(args, parsed_node, &i);
	echo_builtin_cont(parsed_node, &i, is_nflag);
}
