#include "../head/minishell.h"

// CREATE COMMAND DOUBLE ARRAY
// dis shit only works for one (just for testing)
void init_args(t_hold *hold)
{
	char	*tmp;
	char	*tmp_tmp = NULL;

	// otherwise strjoin will not work
	tmp = malloc(sizeof(char));
	tmp = "\0";
	t_lexing *tmp_lex;
	tmp_lex = hold->lex_struct;

	while (tmp_lex != NULL)
	{
		if (tmp_lex->macro == BUILTIN || tmp_lex->macro == WORD)
		{
			while (tmp_lex->macro == BUILTIN || tmp_lex->macro == WORD)
			{
				tmp_tmp = ft_strjoin(tmp, tmp_lex->item);
				tmp = ft_strjoin(tmp_tmp, " ");
				free(tmp_tmp);
				if (tmp_lex->next == NULL)
					break;
				tmp_lex = tmp_lex->next;
			}
			add_node_args(hold, ft_split(tmp, ' '));
			free(tmp);
			tmp = malloc(sizeof(char));
			tmp = "\0";
		}
		if (tmp_lex->next == NULL)
			break;
		tmp_lex = tmp_lex->next;
	}
// print_args(hold);
// exit(0);
}

void get_path(t_hold *hold, char **env, int32_t cmd_index)
{
// CREATE COMMAND DOUBLE ARRAY
	int32_t		i;
	int32_t		k;
	char		**splitted_path;

	i = 0;
	k = 0;
	while (ft_strncmp(env[i], "PATH=/", 6) != 0)
		i++;
	splitted_path = ft_split(env[i] + 5, ':');
	while (splitted_path[k] != NULL)
	{
		splitted_path[k] = ft_strjoin(splitted_path[k], "/");
		hold->valid_path = ft_strjoin(splitted_path[k], hold->args_struct->arg_array[0]);
		if (access(hold->valid_path, F_OK | X_OK) == 0)
			break ;
		free(hold->valid_path);
		k++;
	}
	if (access(hold->valid_path, F_OK | X_OK) != 0)
	{
		ft_putstr_fd(hold->args_struct->arg_array[cmd_index], 2);
		exit_status(hold, ":"RED" COMMAND NOT FOUND\n"RESET, 127);
		return ;
	}
	printf("path: "GRN"%s\n"RESET, hold->valid_path);
}

void executer(t_hold *hold, char **env)
{
	if (hold->exit_code != 0)
		return ;
	init_args(hold);
	print_args(hold);

	// cmd index defines which iteration of args, later implement in while loop
	int32_t cmd_index = 0;
	get_path(hold, env, cmd_index);

// printf(RED"EXIT in executer after get path\n"RESET);
// exit(0);
	// redirect shit

	int pid = fork();
	if (pid == 0)
	{
		// execute shit
		if (execve(hold->valid_path, hold->args_struct->arg_array, env) == -1)
		{
			exit_status(hold, RED"COMMAND NOT FOUND: "RESET, 69);
			ft_putstr_fd(hold->args_struct->arg_array[0], 2);
			write(2, "\n", 1);
			return;
		}
	}
	waitpid(-1, NULL, 0);
	free(hold->valid_path);
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

	hold->lex_struct = NULL;
	hold->args_struct = NULL;

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

		lexer(hold);
		parser(hold);

		if (hold->exit_code == 0)
			print_macro_list(hold->lex_struct);
		
		executer(hold, env);

		free(hold->line);
		free_list_lex(hold->lex_struct);
		free_list_arg(hold->args_struct);
		hold->lex_struct = NULL;
		hold->args_struct = NULL;

	}
	printf(RED"out of loop\n"RESET);
	clear_history();
	// here func to clear all memory
}

//!!!URGENT:


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//!  GENERAL:
// - add history stuff -> should work like this √
// - move cursor bums
// - create env/export list
// - how to store prev return value for $? ?

//!  LEXER: √

//!  PARSER:
// - !do env/export shit in parser first
// - throw error if redir signs at the very end --> do in parser
// - check words for access to figure out if its a valid command (current path with appending word to the end)
//		-> if first parameter is not a command, quit !! --> not real bash behaiviour (figure out what else it could be (eg redir sign))

//!  EXECUTER:
// - include pipex approach and test stuff
//		-> execute:
//			- 'ls'	√
//			- 'ls -l' 


// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
//!  LATER:
// - after main loop clear all memory
// - signals shit
// - transfer lexed list first to parsed list
