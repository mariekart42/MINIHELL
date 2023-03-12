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

// Add clear_history when ready
// Use all appropiate freeing when ready
void	free_all(t_hold *hold)
{
	free_content(&hold);
	// free_env_export(hold);
	free(hold);
	// clear_history;
}

void	exit_builtin(t_hold *hold, t_parsed_chunk *parsed_node)
{
	int32_t	exit_code;

	if (parsed_node->args[1] && parsed_node->args[2])
	{
		exit_status(hold, RED"minishell: exit: too many arguments\n"RESET, 1);
		return ;
	}
	if (parsed_node->args[1] != NULL)
	{
		exit_code = ft_atoi_mod(parsed_node->args[1]);
		if (exit_code == -1)
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(parsed_node->args[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			hold->exit_code = 255;
		}
		else
			hold->exit_code = exit_code;
	}
	else
		hold->exit_code = 0;
	// free_all(hold);
	exit(hold->exit_code % 256);
}
