#include "../head/minishell.h"

// void env_builtin(t_hold *hold)
// {
	
// }
// void export_builtin(t_hold *hold)
// {

// }
// void pwd_builtin(t_hold *hold)
// {

// }
// void cd_builtin(t_hold *hold)
// {

// }
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
		// if (ft_strncmp(hold->lex_struct->item, "env", 3) == 0)
		// 	return (env_builtin(hold), true);
		// else if (ft_strncmp(hold->lex_struct->item, "export", 6) == 0)
		// 	return (export_builtin(hold), true);
		// else if (ft_strncmp(hold->lex_struct->item, "pwd", 3) == 0)
		// 	return (pwd_builtin(hold), true);
		// else if (ft_strncmp(hold->lex_struct->item, "cd", 2) == 0)
		// 	return (cd_builtin(hold), true);
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

int main(int32_t argc, char **argv, char **env)
{
	t_hold	*hold = NULL;
	(void) argc;
	(void) argv;

	hold = (t_hold *)malloc(sizeof(t_hold));
	if (!hold)
		return (69);

	hold->lex_struct = (t_lexing*)malloc(sizeof(t_lexing));
	if (!hold->lex_struct)
		return (69);

	hold->args_struct = (t_args*)malloc(sizeof(t_args));
	if (!hold->args_struct)
		return (69);

	// hold->env_struct = (t_env*)malloc(sizeof(t_env));
	// if (!hold->env_struct)
	// 	return (69);

	hold->lex_struct = NULL;
	hold->args_struct = NULL;
	// hold->env_struct = NULL;

	// using signal function here to catch signal if eg ctr-c is used

	while (1)
	{
		hold->exit_code = 0;
		hold->line = readline(BLU"MINIHELL> "RESET);
		if (!hold->line)
			break ;

		// add_history to update history with current line
		if (ft_strlen(hold->line) > 0)
			add_history(hold->line);

		lexer(hold, env);
		parser(hold);

		if (hold->exit_code == 0)
			print_macro_list(hold->lex_struct);

		if (builtin(hold) == false)
		{
			executer(hold, env);
		}

		free(hold->line);
		free_list_lex(hold->lex_struct);
		free_list_arg(hold->args_struct);
		// free_list_arg(hold->env_struct);
		hold->lex_struct = NULL;
		// hold->env_struct = NULL;
		hold->args_struct = NULL;

	}
	printf(RED"out of loop\n"RESET);
	clear_history();
	// here func to clear all memory
}

//!!!NEXT:
// - move around with cd
// - exit with exit command -> returns 0


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//!  GENERAL:
// - add history stuff -> should work like this √
// - move cursor bums
// - create env/export list
// - how to store prev return value for $? ?
// - when just pressing enter (no input) do nothing and return 0
// - handle also relativ paths


//!  LEXER: √

//!  PARSER:
// - !do env/export shit in parser first
// - throw error if redir signs at the very end --> do in parser
// - check words for access to figure out if its a valid command (current path with appending word to the end)
//		-> if first parameter is not a command, quit !! --> not real bash behaiviour (figure out what else it could be (eg redir sign))

//!  EXECUTER:
// - include pipex approach and test stuff
//		-> execute:
//			- ls  √
//			- ls -l  √
//			- touch test.txt  √
//			- echo $?

// - builtins:
//		- env 
//		- export
//		- pwd 
//		- cd
//		- unset
//		- echo
//		- exit


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//!  LATER:
// - after main loop clear all memory
// - signals shit
// - transfer lexed list first to parsed list
