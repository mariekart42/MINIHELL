#include "../inc/minishell.h"

/* function changes the filedescriptors always
 * 		- from stdin to 'infile' in 'parsed_chunk'
 *		- and from stdout to 'outfile' in 'parsed_chunk' */
void redirection(t_parsed_chunk *parsed_node)
{
	dup2(parsed_node->infile, STDIN_FILENO);
	dup2(parsed_node->outfile, STDOUT_FILENO);
}

void open_pipefds(t_hold *hold, int32_t pipe_groups)
{
	int32_t i;
	i = 0;
	while (i < pipe_groups)
	{
		if (pipe(hold->parsed_list->pipe_fds[i]) < 0)
			exit_status(hold, "Error! Failed to open pipe fd's in open_pipefds()!\n", 69);
		i++;
	}
}

void close_fds(t_parsed_chunk *parsed_node, int32_t pipegroups)
{
	int32_t i;

	i = 0;
	while (i < pipegroups)
	{
		close(parsed_node->pipe_fds[i][0]);
		close(parsed_node->pipe_fds[i][1]);
		i++;
	}

}

void execute_cmd(t_parsed_chunk *parsed_node, char **my_env)
{
	if (execve(parsed_node->cmd_path, parsed_node->args, my_env) < 0)
	{
		ft_putstr_fd("Error! Failed to execve in execute_cmd()\n", 2);
		write(2, "EXIT here, later handle error different!\n", 42);
		exit(69);
	}
}

char **list_to_char_array(t_env_export *env_node)
{
	t_env_export *tmp;
	int32_t	env_len;
	char	**env_array;
	int32_t		i;

	tmp = env_node;
	env_len = 0;
	i = 0;
	while (tmp != NULL)
	{
		env_len++;
		tmp = tmp->next;
	}
	tmp = env_node;
	env_array = malloc(sizeof(char*) * env_len);
	while (i < env_len)
	{
		env_array[i] = ft_strdup(tmp->item);
		tmp = tmp->next;
		i++;
		env_len--;
	}
	return (env_array);
}

void executer(t_hold *hold)
{
	printf("in executer\n");
	int32_t *pids;
	int32_t pipegroups;
	int32_t	i;
	t_parsed_chunk *parsed_node;
	// int32_t pipe_fds[MAX_FD][2];

	parsed_node = hold->parsed_list;
	write(2, GRN"check\n"RESET, 11);
	if (hold->exit_code != 0)
	{
		printf("exit_code: %d\n", hold->exit_code);
		return ;
	}
	// print_parsed_list(hold->parsed_list);

	pipegroups = count_pipegroups(hold->lex_struct);

	// malloc array with process-id's for forking:
	pids = malloc(sizeof(int32_t) * pipegroups);
	if (!pids)
		return (exit_status(hold, "Error! Failed to malloc for pids (in executer())\n", 69));

	// open amount of pipes we need (one pipegroup = one pipe)
	open_pipefds(hold, pipegroups);

	i = 0;
	while (pipegroups > 0)
	{
		pids[i] = fork();
		if (pids[i] == 0)
		{
			// redirection (dup2())
			redirection(parsed_node);

			// close filediscriptors (pipes and files)
			close_fds(parsed_node, pipegroups);

			// execute command
			execute_cmd(parsed_node, list_to_char_array(hold->env_list));
		}

		pipegroups--;
	}

	// loop where we wait for kiddos to finish
	waitpid(pids[i], NULL, 0);
}