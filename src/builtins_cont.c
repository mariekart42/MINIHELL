#include "minishell.h"

// Good reference
// https://man7.org/linux/man-pages/man1/cd.1p.html
void cd_builtin(t_hold *hold, t_parsed_chunk *parsed_node)
{

}

// If no directory operand is given and the HOME environment
// variable is empty or undefined, the default behavior is
// implementation-defined and no further steps shall be taken.

// If no directory operand is given and the HOME environment
// variable is set to a non-empty value, the cd utility shall
// behave as if the directory named in the HOME environment
// variable was specified as the directory operand.

///////////////////////////

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


///////////////////

// void exit_builtin(t_hold *hold)
// {

// }

// void unset_builtin(t_hold *hold)
// {

// }

