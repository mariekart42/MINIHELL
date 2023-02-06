#include "../head/minishell.h"

// --- just for printing args (delete later) ---
void print_args(t_hold *hold)
{
int32_t i = 0;
printf("ARGS:\n");
while (hold->args[i] != NULL)
{
	printf("[%d]: %s\n",i, hold->args[i]);
	i++;
}
if (hold->args[i] == NULL)
	printf("(NULL)\n\n");
}
// ---------------------------------------------

// CREATE COMMAND DOUBLE ARRAY
// dis shit only works for one (just for testing)
void init_args(t_hold *hold)
{
	while (hold->lexed_list != NULL)
	{
		if (hold->lexed_list->macro == BUILTIN || hold->lexed_list->macro == WORD)
		{
			hold->args = ft_split(hold->lexed_list->item, '\0');
			break;
		}
		hold->lexed_list = hold->lexed_list->next;
	}
// print_args(hold);

}

void get_path(t_hold *hold, char **env)
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
		hold->valid_path = ft_strjoin(splitted_path[k], hold->args[0]);
		if (access(hold->valid_path, F_OK | X_OK) == 0)
			break ;
		free(hold->valid_path);
		k++;
	}
}

void executer(t_hold *hold, char **env)
{
	if (hold->exit_code != 0)
		return ;
	init_args(hold);
	// find path
	// -> check for access (if command exist)
	get_path(hold, env);

	// redirect shit

	int pid = fork();
	if (pid == 0)
	{
		// execute shit
		if (execve(hold->valid_path, hold->args, env) == -1)
		{
			exit_status(hold, RED"COMMAND NOT FOUND: "RESET, 69);
			ft_putstr_fd(hold->args[0], 2);
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
	hold->lexed_list = (t_lexing*)malloc(sizeof(t_lexing));
	if (!hold->lexed_list)
		return (69);

	hold->lexed_list = NULL;
	hold->exit_code = 0;

	// using signal function here to catch signal if eg ctr-c is used

	while (1)
	{
		hold->line = readline(BLU"MINIHELL> "RESET);
		if (!hold->line)
			break ;

		// add_history to update history with current line
		if (ft_strlen(hold->line) > 0)
			add_history(hold->line);

		lexer(hold);
		parser(hold);

		if (hold->exit_code == 0)
			print_macro_list(hold->lexed_list);
		
		executer(hold, env);

		free(hold->line);
		freeList(hold->lexed_list);
		hold->lexed_list = NULL;

	}
	printf(RED"out of loop\n"RESET);
	// here func to clear all memory
}


//GENERAL:
// - add history stuff -> move cursor bums

// - create env/export list

// - how to store prev return value for $?


//LEXER:


//PARSER:
// !do env/export shit in parser first

// - throw error if redir signs at the very end --> do in parser

// - check words for access to figure out if its a valid command (current path with appending word to the end)
//	-> if first parameter is not a command, quit !! --> not real bash behaiviour (figure out what else it could be (eg redir sign))

//EXECUTER:
// - include pipex approach and test stuff
//	-> execute:
//		- 'ls'		-> works
//		- 'ls -l' 



//LATER:
// - after main loop clear all memory

// - signals shit

// - transfer lexed list first to parsed list