#include "../inc/minishell.h"

/* function changes the filedescriptors always
 * 		- from stdin to 'infile' in 'parsed_chunk'
 *		- and from stdout to 'outfile' in 'parsed_chunk' */
void redirection(t_parsed_chunk *parsed_node, int32_t i, int32_t pipegroups, int32_t pipe_fds[MAX_FD][2])
{
	// printf("%d %d\n", i, pipegroups);
	if (i == 0)
	{
		if (parsed_node->infile != 0)
			dup2(parsed_node->infile, STDIN_FILENO);
		if (pipegroups > i+1) // there is another pipegroup afterwards
		{
			if (parsed_node->outfile != 1)
			{
				write(2, "uhm outfile before pipe, duh? (how to handle redir?) | EXIT\n", 60);
				exit(0);
			}
			dup2(pipe_fds[i][1], STDOUT_FILENO);
		}
		else
		{
			if (parsed_node->outfile != 1)
				dup2(parsed_node->outfile, STDOUT_FILENO);
		}
	}
	else if ((i+1) == pipegroups) // end of pipegroups
	{
		// pipe(pipe_fds[i + 1]);
		dup2(pipe_fds[i - 1][0], STDIN_FILENO);
		// printf("last pipe %d\n", pipe_fds[i - 1][0]);

		if (parsed_node->outfile != 1)
			dup2(parsed_node->outfile, STDOUT_FILENO);
	}
	else // in the middle of pipegroups
	{
		dup2(pipe_fds[i][0], parsed_node->infile);
		dup2(pipe_fds[i][1], parsed_node->outfile);
	}
}

void open_pipefds(int32_t pipegroups, int32_t pipe_fds[MAX_FD][2])
{
	int32_t i;

	i = 0;
	while (i + 1< pipegroups)
	{
		// write(2, "opend pipe\n", 11);
		if (pipe(pipe_fds[i]) < 0)
		{
			exit_status("Error! Failed to open pipe!\n", 69);
			exit(0);
		}
		i++;
	}
}

void close_fds(t_hold *hold, int32_t pipegroups, int32_t pipe_fds[MAX_FD][2])
{
	int32_t i;
	t_parsed_chunk *tmp;

	i = 0;
	tmp = hold->parsed_list;
	while ((i+1) < pipegroups)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		i++;
	}
	while (tmp != NULL)
	{
		if (tmp->infile != 0)
			close(tmp->infile);
		if (tmp->outfile != 1)
			close(tmp->outfile);
		tmp = tmp->next;
	}
}

void execute_cmd(t_parsed_chunk *parsed_node, char **ori_env)
{
	if (execve(parsed_node->cmd_path, parsed_node->args, ori_env) == -1)
	{
		write(2, RED"minihell: ", 16);
		write(2, parsed_node->args[0], ft_strlen(parsed_node->args[0]));
		exit_status(RED": command not found!\n"RESET, 69);
		// exit(127);
	}
	// printf("lskjdfh: %s\n",hold->valid_path);
	// exit(1);
}

void handle_here_doc(t_parsed_chunk *pars_node)
{
	char	*input_string;
	char *tmp1;
	char *tmp2;

	input_string = NULL;
	tmp1 = NULL;
	tmp2 = malloc(1);
	tmp2[0] = '\0';

	if (pars_node->here_doc_delim == NULL)
		write(2, "problem with delim in handle_here_doc\n", 38);
printf("infile: %d\n", pars_node->infile);
	heredoc_sig(); // Signal goes before input of hierdoc
	while (1)
	{
		input_string = readline(CYN"heredoc> "RESET);
		if (ft_strncmp(input_string, pars_node->here_doc_delim, ft_strlen(pars_node->here_doc_delim)) == 0 && (ft_strlen(pars_node->here_doc_delim) == ft_strlen(input_string)))
		{
			ft_putstr_fd(tmp2, pars_node->infile);
			free(tmp2);
			free(input_string);
			break;
		}
		if (tmp1 == NULL)
		{
			tmp1 = ft_strdup(input_string);
			tmp2 = ft_strjoin(tmp1, "\n");
			free(tmp1);
		}
		else
		{
			tmp1 = ft_strjoin(tmp2, input_string);
			free(tmp2);
			tmp2 = ft_strjoin(tmp1, "\n");
			free(tmp1);
		}
		free(input_string);
	}
	close(pars_node->infile);
	pars_node->infile = open("tmp.hd", O_CREAT | O_RDONLY , 0777);
}

void handle_single_builtin(t_hold *hold)
{
	// printf("single builtin handeler\n");
	if (hold->parsed_list->here_doc_delim != NULL)
		handle_here_doc(hold->parsed_list);
	// redir

	// clode fds
	if (hold->parsed_list->infile != 0)
		close(hold->parsed_list->infile);
	if (hold->parsed_list->outfile != 1)
		close(hold->parsed_list->outfile);

	builtin(hold, hold->parsed_list);
}

void executer(t_hold *hold, char **ori_env)
{
	int32_t *pids;
	int32_t pipegroups;
	int32_t	i;
	t_parsed_chunk *parsed_node;
	int32_t pipe_fds[MAX_FD][2];

	parsed_node = hold->parsed_list;
	if (error_code != 0)
		return ;
	pipegroups = count_pipegroups(hold->lex_struct);
	if (pipegroups == 1 && hold->lex_struct->macro == BUILTIN)
		return (handle_single_builtin(hold));
	pids = malloc(sizeof(int32_t) * (pipegroups));
	if (!pids)
		return (exit_status(MAG"Error! Failed to malloc for pids (in executer())\n"RESET, 69));
	open_pipefds(pipegroups, pipe_fds);
	i = 0;
	while (i < pipegroups)
	{
		pids[i] = fork();

		if (pids[i] == 0)
		{
			child_sig();
			if (parsed_node->here_doc_delim != NULL)
			{
				// printf("%s\n", parsed_node->here_doc_delim);
				handle_here_doc(parsed_node);
			}
			redirection(parsed_node, i, pipegroups, pipe_fds);

			close_fds(hold, pipegroups, pipe_fds);
			if (builtin_parser(parsed_node->args[0]) == true)
				builtin(hold, parsed_node);
			else
				execute_cmd(parsed_node, ori_env);
			exit(69);
		}
		else
		{
			// close_all_fds(parsed_node, pipe_fds, i, pipegroups);
			// waitpid(pids[i], NULL, 0);
			close(pipe_fds[i][1]);
			if (i != 0)
				close(pipe_fds[i-1][0]);
			if (parsed_node->infile != 0)
				close(parsed_node->infile);
			if (parsed_node->outfile != 1)
				close(parsed_node->outfile);
		}
		i++;
		parsed_node = parsed_node->next;
	}
	close(pipe_fds[i-1][0]);

		// close(pipe_fds[i][0]); // not sure which 
	// close(pipe_fds[i][0]); // one of these two

	i = 0;
	// while (pids[i])
	while ((i < pipegroups) && (pids[i]))
	{
		waitpid(pids[i], &error_code, WUNTRACED);
		if (error_code != 0)
			exit_status("", 69);
		i++;
	}
	free(pids);
	pids = NULL;
}
