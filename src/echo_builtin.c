#include "minishell.h"

bool	echo_builtin_helper(t_parsed_chunk *parsed_node, int i, bool is_nflag)
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

void	echo_builtin(t_parsed_chunk *parsed_node)
{
	char	**args;
	int		i;
	bool	is_nflag;
	bool	temp_flag;

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
