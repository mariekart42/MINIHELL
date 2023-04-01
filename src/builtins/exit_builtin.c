#include "minishell.h"

int	ft_atoi_mod(const char *str)
{
	long int	output;
	long int	sign;
	int			i;

	output = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		output = output * 10 + (str[i] - '0');
		i++;
	}
	return (sign * output);
}

bool	multiple_args(t_pars *parsed_node)
{
	if (parsed_node->args[1] && parsed_node->args[2])
	{
		ft_putstr_fd("exit\n", 2);
		exit_status("exit: too many arguments", "", "", 1);
		return (true);
	}
	return (false);
}

void	exit_builtin(t_hold *hold, t_pars *parsed_node)
{
	int32_t	exit_code;

	if (parsed_node->args[1])
	{
		if (multiple_args(parsed_node))
			return ;
		exit_code = ft_atoi_mod(parsed_node->args[1]);
		if (exit_code == -1 || ft_strncmp(parsed_node->args[1], "-\0", 2) == 0)
		{
			ft_putstr_fd("exit\n", 2);
			exit_status("exit:", parsed_node->args[1],
				": numeric argument required", 255);
			free_exit(hold);
			exit(255);
		}
		else
			g_error_code = exit_code % 256;
	}
	else
		g_error_code = 0;
	free_exit(hold);
	ft_putstr_fd("exit\n", 2);
	exit(g_error_code);
}
