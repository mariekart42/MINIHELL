// #include "minishell.h"

// // https://man7.org/linux/man-pages/man1/unset.1p.html

// void	delete_var (t_hold)

// int	find_var(t_hold *hold, char *var)
// {


// 	return (0);
// }


// void unset_builtin(t_hold *hold, t_parsed_chunk *parsed_node)
// {
// 	char	**args;
// 	int		i;

// 	args = parsed_node->args;
// 	i = 1;
// 	while (args[i] != NULL)
// 	{
// 		if (find_var(hold, args[i]) == -1)
// 		{
// 			ft_putstr_fd(RED"minshell: unset: ", 2);
// 			ft_putstr_fd(args[i], 2);
// 			exit_status(hold, ": not a valid identifier\n"RESET, 69);
// 			return ;
// 		}
// 		else
			
// 		i++
// 	}
// }

// // void export_builtin(t_hold *hold)
// // {
// // }