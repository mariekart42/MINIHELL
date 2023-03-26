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

void	exit_builtin(t_parsed_chunk *parsed_node)
{
	int32_t	exit_code;

	if (parsed_node->args[1])
	{
		exit_code = ft_atoi_mod(parsed_node->args[1]);
		if (exit_code == -1)
		{
			ft_putstr_fd(RED"minishell: exit: ", 2);
			ft_putstr_fd(parsed_node->args[1], 2);
			ft_putstr_fd(": numeric argument required\n"RESET, 2);
			exit(255);
		}
		else
			error_code = exit_code;
		if (parsed_node->args[1] && parsed_node->args[2])
		{
			exit_status(RED"minishell: exit: too many arguments\n"RESET, 1);
			return ;
		}
	}
	else
		error_code = 0;
	exit(error_code % 256);
}
