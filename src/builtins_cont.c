#include "minishell.h"

// void cd_builtin(t_hold *hold)
// {
// 	if (hold->lex_struct->next->item == NULL)
// 	{
// 		printf(RED"adding homedirectory feature later!\nEXIT\n"RESET);
// 		exit(0);
// 	}
// 	// get $HOME from own env list and give it to chrir as an argument
	
// 	if (chdir(hold->lex_struct->next->item) < 0)
// 	{
// 		ft_putstr_fd(RED"", 2); //just for making it red lol
// 		write(1, hold->lex_struct->next->item, ft_strlen(hold->lex_struct->next->item));
// 		exit_status(hold, ": NO SUCH FILE OR DIRECTORY\n"RESET, 69);
// 		return ;
// 	}
// }

// void exit_builtin(t_hold *hold)
// {

// }

// void unset_builtin(t_hold *hold)
// {

// }
