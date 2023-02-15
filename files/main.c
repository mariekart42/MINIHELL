/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 15:00:57 by mmensing          #+#    #+#             */
/*   Updated: 2023/02/15 20:39:13 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../head/minishell.h"

void env_builtin(t_hold *hold)
{
	t_env_export *tmp;
	
	tmp = hold->env_list;
	while (tmp != NULL)
	{
		ft_putstr_fd(tmp->item, 2);
		write(2, "\n", 1);
		tmp = tmp->next;
	}
}

void export_builtin(t_hold *hold)
{
	t_env_export *tmp;
	
	tmp = hold->export_list;
	while (tmp != NULL)
	{
		ft_putstr_fd(tmp->item, 2);
		write(2, "\n", 1);
		tmp = tmp->next;
	}
}

/* bash:	If the current working directory is a symbolic link that points to a 
 * 			directory that no longer exists, the pwd command will fail with a 
 * 			"No such file or directory" error								*/
void pwd_builtin(t_hold *hold)
{
	char	path[PATH_MAX];
	
	if (!getcwd(path, PATH_MAX))
	{
		exit_status(hold, RED"PWD: NO SUCH FILE OR DIRECTORY\n"RESET, 69);
		return ;
	}
	write(2, path, ft_strlen(path));
	write(2, "\n", 1);
}

void cd_builtin(t_hold *hold)
{
	if (hold->lex_struct->next->item == NULL)
	{
		printf(RED"adding homedirectory feature later!\nEXIT\n"RESET);
		exit(0);
	}
	// get $HOME from own env list and give it to chrir as an argument
	
	if (chdir(hold->lex_struct->next->item) < 0)
	{
		ft_putstr_fd(RED"", 2); //just for making it red lol
		write(2, hold->lex_struct->next->item, ft_strlen(hold->lex_struct->next->item));
		exit_status(hold, ": NO SUCH FILE OR DIRECTORY\n"RESET, 69);
		return ;
	}

}


// void unset_builtin(t_hold *hold)
// {

// }
// void echo_builtin(t_hold *hold)
// {

// }
// void exit_builtin(t_hold *hold)
// {

// }

bool builtin(t_hold *hold)
{
	if (hold->lex_struct->macro == BUILTIN)
	{
		// printf(MAG"BUILTIN\n"RESET);
		if (ft_strncmp(hold->lex_struct->item, "env", 3) == 0)
			return (env_builtin(hold), true);
		else if (ft_strncmp(hold->lex_struct->item, "export", 6) == 0)
			return (export_builtin(hold), true);
		else if (ft_strncmp(hold->lex_struct->item, "pwd", 3) == 0)
			return (pwd_builtin(hold), true);
		else if (ft_strncmp(hold->lex_struct->item, "cd", 2) == 0)
			return (cd_builtin(hold), true);
		// else if (ft_strncmp(hold->lex_struct->item, "unset", 5) == 0)
		// 	return (unset_builtin(hold), true);
		// else if (ft_strncmp(hold->lex_struct->item, "echo", 4) == 0)
		// 	return (echo_builtin(hold), true);
		// else if (ft_strncmp(hold->lex_struct->item, "exit", 4) == 0)
		// 	return (exit_builtin(hold), true);
		return (true);
	}
	else
		return (false);
}

void free_content(t_hold *hold)
{
	free(hold->line);
	free_list_lex(hold->lex_struct);
	free_list_data(hold->data_struct);
	hold->lex_struct = NULL;
	hold->data_struct = NULL;

}

int32_t init_structs(t_hold **hold)
{
	(*hold) = (t_hold *)malloc(sizeof(t_hold));
	if (!(*hold))
		return (69);
	(*hold)->lex_struct = (t_lexing*)malloc(sizeof(t_lexing));
	if (!(*hold)->lex_struct)
		return (69);
	(*hold)->data_struct = (t_data*)malloc(sizeof(t_data));
	if (!(*hold)->data_struct)
		return (69);
	(*hold)->env_list = (t_env_export*)malloc(sizeof(t_env_export));
	if (!(*hold)->env_list)
		return (69);
	(*hold)->export_list = (t_env_export*)malloc(sizeof(t_env_export));
	if (!(*hold)->export_list)
		return (69);
	(*hold)->lex_struct = NULL;
	(*hold)->data_struct = NULL;
	(*hold)->env_list = NULL;
	(*hold)->export_list = NULL;
	return (0);
}

void free_env_export(t_hold *hold)
{
	
	free_list_env(hold->env_list);
	free_list_env(hold->export_list);
	hold->env_list = NULL;
	hold->export_list = NULL;

}

int main(int32_t argc, char **argv, char **env)
{
	t_hold	*hold = NULL;
	(void) argc;
	(void) argv;

	if (init_structs(&hold))
		return (69);

	// using signal function here to catch signal if eg ctr-c is used
	create_env_export_list(hold, env);

	while (1)
	{
		hold->exit_code = 0;
		hold->line = readline(BLU"MINIHELL> "RESET);
		if (!hold->line)
			break ;
		
		// if line is empty, bash returns 0 and does nothing
		if (ft_strlen(hold->line) > 0)
		{
			add_history(hold->line);

			lexer(hold);
			
			parser(hold);

			if (hold->exit_code == 0)
				print_macro_list(hold->lex_struct);

			if (builtin(hold) == false)
			{
				// printf(RED"NO BUILTIN: EXIT\n"RESET);
				// exit(0);
				executer(hold, env);
			}
			free_content(hold);
			
		}
	}
	free_env_export(hold);
	clear_history();
	// here func to clear all memory
}

//!!!NEXT:
// - export list: order alpahteically + add var_name to struct


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//!  GENERAL:
// - move cursor bums
// - how to store prev return value for $? ?
// - handle also relativ paths


//!  LEXER: √

//!  PARSER:
// - !do env/export shit in parser first
// - throw error if redir signs at the very end --> do in parser
// - check words for access to figure out if its a valid command (current path with appending word to the end)
//		-> if first parameter is not a command, quit !! --> not real bash behaiviour (figure out what else it could be (eg redir sign))

//!  EXECUTER:
// - later: put builtin stuff into executer (not as bool in main!)

// - builtins:
//		- env √
//		- export
//		- pwd √
//		- cd √ (for now)
//		- unset
//		- echo
//		- exit


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//!  LATER:
// - after main loop clear all memory
// - exit with exit command -> returns 0
// - signals shit
// - transfer lexed list first to parsed list
