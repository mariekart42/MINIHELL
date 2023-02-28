#include "minishell.h"

// Reference
// https://man7.org/linux/man-pages/man1/cd.1p.html
// https://man7.org/linux/man-pages/man3/chdir.3p.html
void cd_builtin(t_hold *hold, t_parsed_chunk *parsed_node)
{
	char	*home;
	bool	is_home;
	char	**args;
	t_env_export *tmp;
	
	is_home = true;
	args = parsed_node->args;
	tmp = hold->env_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var_name, "HOME", 4) == 0)
			home = tmp->var_value;
		tmp = tmp->next;
	}
	free(tmp);
	if (home == '\0')
		is_home = false;
	
	if (args[1] == NULL)
	{
		if (is_home)
			// Change to HOME
		else
		{
			// Error Ask Starky / Wolf
			exit_status(hold, RED"minishell: cd: HOME not set\n"RESET, 69);
			return ;
		}
	}

}

// cd / -> / (Absolute directory)
// cd or cd ~ -> HOME


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

