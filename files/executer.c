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
		hold->valid_path = ft_strjoin(splitted_path[k], hold->args_struct->arg_array[cmd_index]);
		if (access(hold->valid_path, F_OK | X_OK) == 0)
			break ;
		free(hold->valid_path);
		k++;
	}
	if (access(hold->valid_path, F_OK | X_OK) != 0)
	{
		// ft_putstr_fd(hold->args_struct->arg_array[cmd_index], 2);
		// exit_status(hold, ":"RED" COMMAND NOT FOUND\n"RESET, 127);
		return ;
	}
	printf("path: "GRN"%s\n"RESET, hold->valid_path);
}

void executer(t_hold *hold, char **env)
{
	if (hold->exit_code != 0)
		return ;
	init_args(hold);
	printf("check exec\n");
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
			ft_putstr_fd(hold->args_struct->arg_array[cmd_index], 2);
			exit_status(hold, ":"RED" COMMAND NOT FOUND\n"RESET, 127);
			return ;
			// exit_status(hold, RED"COMMAND NOT FOUND: "RESET, 69);
			// ft_putstr_fd(hold->args_struct->arg_array[0], 2);
			// write(2, "\n", 1);
			// return;
		}
	}
	waitpid(-1, NULL, 0);
	free(hold->valid_path);
}
