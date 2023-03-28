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

void	free_exit(t_hold *hold)
{
	free_content(&hold);
	free(hold->line);
	free_env_export(hold);
	free(hold);
}

void	exit_builtin(t_hold *hold, t_pars *parsed_node)
{
	int32_t	exit_code;

	if (parsed_node->args[1])
	{
		if (parsed_node->args[1] && parsed_node->args[2])
		{
			exit_status("exit: too many arguments", "", "", 1);
			return ;
		}
		exit_code = ft_atoi_mod(parsed_node->args[1]);
		if (exit_code == -1)
		{
			exit_status("exit:", parsed_node->args[1],
				": numeric argument required", 255);
			exit(255);
		}
		else
			error_code = exit_code;
	}
	else
		error_code = 0;
	free_exit(hold);
	exit(error_code % 256);
}
