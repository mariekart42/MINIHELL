#include "minishell.h"

void	exit_status(char *msg1, char *msg2, char *msg3, int32_t exit_code_)
{
	write(2, RED"minishell: ", 16);
	write(2, msg1, ft_strlen(msg1));
	write(2, " ", 1);
	write(2, msg2, ft_strlen(msg2));
	write(2, " ", 1);
	write(2, msg3, ft_strlen(msg3));
	write(2, ""RESET, 7);
	g_error_code = exit_code_ % 255;
}

void	print_error_code(void)
{
	char	*error;

	error = ft_itoa(g_error_code);
	ft_putstr_fd(error, 1);
	ft_putstr_fd("\n", 1);
	free(error);
	return ;
}

int	ft_isalnum_mod(int val)
{
	if ((val >= 48 && val <= 57) || (val >= 65 && val <= 90) || \
		(val >= 97 && val <= 122) || val == 61 || val == 95)
		return (1);
	return (0);
}
