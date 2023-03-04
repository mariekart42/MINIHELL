#include "minishell.h"

// https://man7.org/linux/man-pages/man1/exit.1p.html
void exit_builtin(t_hold *hold, t_parsed_chunk *parsed_node)
{
	int32_t	old_exit_code;

	old_exit_code = hold->exit_code;
	if (parsed_node->args[2] != NULL)
	{
		exit_status(hold, RED"minishell: exit: too many arguments\n"RESET, 69);
		return ;
	}
	if (parsed_node->args[1] == NULL)
	{
		exit_status(hold, RED""RESET, old_exit_code);
	}
	if (parsed_node->args[1] != NULL)
	{
		if (parsed_node->args[1] > 0 && parsed_node->args[1] <= 256)
			exit_status(hold, RED""RESET, parsed_node->args[1] % 256); //ft_atoi
		else
			//undefined
	}

}

// The exit status shall be n, if specified, except that the
// behavior is unspecified if n is not an unsigned decimal integer
// or is greater than 255. Otherwise, the value shall be the exit
// value of the last command executed, or zero if no command was
// executed.

// void unset_builtin(t_hold *hold)
// {

// }

