#include "../inc/minishell.h"

/* function changes the filedescriptors always
 * 		- from stdin to 'infile' in 'parsed_chunk'
 *		- and from stdout to 'outfile' in 'parsed_chunk' */
void redirection(t_pars *parsed_node, int32_t i, int32_t pipegroups, int32_t pipe_fds[MAX_FD][2])
{
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
		dup2(pipe_fds[i - 1][0], STDIN_FILENO);
		if (parsed_node->outfile != 1)
			dup2(parsed_node->outfile, STDOUT_FILENO);
	}
	else // in the middle of pipegroups
	{
		dup2(pipe_fds[i-1][0], STDIN_FILENO);
		dup2(pipe_fds[i][1], STDOUT_FILENO);
	}
}

void open_pipefds(int32_t pipegroups, int32_t pipe_fds[MAX_FD][2])
{
	int32_t i;

	i = 0;
	while (i + 1< pipegroups)
	{
		if (pipe(pipe_fds[i]) < 0)
		{
			exit_status("Error! Failed to open pipe!", "", "", 69);
			exit(1);
		}
		i++;
	}
}

void close_fds_child(t_hold *hold, int32_t pipegroups, int32_t pipe_fds[MAX_FD][2])
{
	int32_t i;
	t_pars *tmp;

	i = 0;
	tmp = hold->pars_list;
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

void execute_cmd(t_pars *parsed_node, char **ori_env)
{
	if (execve(parsed_node->cmd_path, parsed_node->args, ori_env) == -1)
		exit_status(parsed_node->args[0], ":command not found!", "", 127);
}

void handle_here_doc(t_pars *pars_node)
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
	int32_t tmp_in;
	int32_t tmp_out;

	if (hold->pars_list->here_doc_delim != NULL)
		handle_here_doc(hold->pars_list);
	tmp_in = dup(STDIN_FILENO);
	tmp_out = dup(STDOUT_FILENO);
	dup2(hold->pars_list->infile, STDIN_FILENO);
	dup2(hold->pars_list->outfile, STDOUT_FILENO);
	builtin(hold, hold->pars_list);
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	if (hold->pars_list->infile != 0)
		close(hold->pars_list->infile);
	if (hold->pars_list->outfile != 1)
		close(hold->pars_list->outfile);
}

void close_fds_parent(t_pars **parsed_node)
{
	// close(*(pipe_fds[i][1]));
	// if (i != 0)
	// 	close(*(pipe_fds[i-1][0]));
	if ((*parsed_node)->infile != 0)
		close((*parsed_node)->infile);
	if ((*parsed_node)->outfile != 1)
		close((*parsed_node)->outfile);
}

void exec_child(t_hold *hold, t_pars *pars_node, char **ori_env, int32_t pipe_fds[MAX_FD][2])
{
	child_sig(); //Placed at start of child
	if (pars_node->here_doc_delim != NULL)
		handle_here_doc(pars_node);
	close_fds_child(hold, hold->pipegroups, pipe_fds);
	if (builtin(hold, pars_node) == false)
	{
		execute_cmd(pars_node, ori_env);
		exit(122);
	}
	exit(g_error_code);
}

void executer(t_hold *hold, char **ori_env)
{
	int32_t	i;
	t_pars *parsed_node;
	int32_t pipe_fds[MAX_FD][2];

	parsed_node = hold->pars_list;
	if (g_error_code != 0)
		return ;
	if (hold->pipegroups == 1 && hold->lex_struct->macro == BUILTIN)
		return (handle_single_builtin(hold));
	open_pipefds(hold->pipegroups, pipe_fds);
	i = 0;
	while (i < hold->pipegroups)
	{
		if (fork() == 0)
		{
			redirection(parsed_node, i, hold->pipegroups, pipe_fds);
			exec_child(hold, parsed_node, ori_env, pipe_fds);
		}
		else
		{
			close_fds_parent(&parsed_node);
			close(pipe_fds[i][1]);
			if (i != 0)
				close(pipe_fds[i-1][0]);
		}
		i++;
		parsed_node = parsed_node->next;
	}
	close(pipe_fds[i-1][0]);
	i = 0;
	while (i++ < hold->pipegroups)
		waitpid(-1, &g_error_code, WUNTRACED);
}
