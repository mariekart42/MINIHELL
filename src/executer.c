#include "../inc/minishell.h"

void	redir_first(t_pars *pars_node, int32_t pipe_fds[MAX_FD][2], int32_t i, \
															int32_t pipegroups)
{
	if (pars_node->infile != 0)
		dup2(pars_node->infile, STDIN_FILENO);
	if (pipegroups > (i + 1))
	{
		if (pars_node->outfile != 1)
		{
			exit_status("outfile before pipe!", "", "", 69);
			exit(0);
		}
		dup2(pipe_fds[i][1], STDOUT_FILENO);
	}
	else
	{
		if (pars_node->outfile != 1)
			dup2(pars_node->outfile, STDOUT_FILENO);
	}
}

/* function changes the filedescriptors always
 * 		- from stdin to 'infile' in 'parsed_chunk'
 *		- and from stdout to 'outfile' in 'parsed_chunk' */
void	redirection(t_pars *parsed_node, int32_t i, int32_t pipegroups,
			int32_t pipe_fds[MAX_FD][2])
{
	if (i == 0)
		redir_first(parsed_node, pipe_fds, i, pipegroups);
	else if ((i + 1) == pipegroups)
	{
		dup2(pipe_fds[i - 1][0], STDIN_FILENO);
		if (parsed_node->outfile != 1)
			dup2(parsed_node->outfile, STDOUT_FILENO);
	}
	else // in the middle of pipegroups
	{
		dup2(pipe_fds[i - 1][0], STDIN_FILENO);
		dup2(pipe_fds[i][1], STDOUT_FILENO);
	}
}

void	open_pipefds(int32_t pipegroups, int32_t pipe_fds[MAX_FD][2])
{
	int32_t	i;

	i = 0;
	while (i + 1 < pipegroups)
	{
		if (pipe(pipe_fds[i]) < 0)
		{
			exit_status("Error! Failed to open pipe!", "", "", 69);
			exit(1);
		}
		i++;
	}
}

void	close_fds_child(t_hold *hold, int32_t pipegroups,
			int32_t pipe_fds[MAX_FD][2])
{
	int32_t	i;
	t_pars	*tmp;

	i = 0;
	tmp = hold->pars_list;
	while ((i + 1) < pipegroups)
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

void	execute_cmd(t_pars *parsed_node, char **ori_env)
{
	if (execve(parsed_node->cmd_path, parsed_node->args, ori_env) == -1)
		exit_status(parsed_node->args[0], ":command not found!", "", 127);
}

bool	input_is_delim(t_pars *pars_node, char *input_string, char *tmp2)
{
	bool	condition;

	condition = ft_strlen(pars_node->here_doc_delim) == ft_strlen(input_string);
	if (ft_strncmp(input_string, pars_node->here_doc_delim,
			ft_strlen(pars_node->here_doc_delim)) == 0
		&& (condition))
	{
		ft_putstr_fd(tmp2, pars_node->infile);
		free(tmp2);
		free(input_string);
		return (true);
	}
	return (false);
}

void	handle_here_doc_cont(t_pars *pars_node, char *input_string, char *tmp1,
			char *tmp2)
{
	heredoc_sig();
	while (1)
	{
		input_string = readline(CYN"heredoc> "RESET);
		if (input_is_delim(pars_node, input_string, tmp2))
			break ;
		if (tmp1 == NULL)
		{
			tmp1 = ft_strdup(input_string);
			tmp2 = ft_strjoin(tmp1, "\n");
			free(tmp1);
		}
		else
		{
			tmp1 = ft_strnnjoin(tmp2, ft_strlen(tmp2), input_string,
					ft_strlen(input_string));
			free(tmp2);
			tmp2 = ft_strjoin(tmp1, "\n");
			free(tmp1);
		}
		free(input_string);
	}
	close(pars_node->infile);
	pars_node->infile = open("tmp.hd", O_CREAT | O_RDONLY, 0777);
}

void	handle_here_doc(t_pars *pars_node)
{
	char	*input_string;
	char	*tmp1;
	char	*tmp2;

	input_string = NULL;
	tmp1 = NULL;
	tmp2 = NULL;
	if (pars_node->here_doc_delim == NULL)
		return ;
	handle_here_doc_cont(pars_node, input_string, tmp1, tmp2);
}

void	handle_single_builtin(t_hold *hold)
{
	int32_t	tmp_in;
	int32_t	tmp_out;

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

void	close_fds_parent(t_pars **parsed_node)
{
	if ((*parsed_node)->infile != 0)
		close((*parsed_node)->infile);
	if ((*parsed_node)->outfile != 1)
		close((*parsed_node)->outfile);
}

void	exec_child(t_hold *hold, t_pars *pars_node, char **ori_env,
			int32_t pipe_fds[MAX_FD][2])
{
	close_fds_child(hold, hold->pipegroups, pipe_fds);
	if (builtin(hold, pars_node) == false)
	{
		execute_cmd(pars_node, ori_env);
		exit(122);
	}
	exit(g_error_code);
}

int32_t prep_exec(t_hold *hold, int32_t pipe_fds[MAX_FD][2], int32_t *i)
{
	if (g_error_code != 0)
	{
		return (-1);
	}
	if (hold->pipegroups == 1 && hold->lex_struct->macro == BUILTIN)
	{
		handle_single_builtin(hold);
		return (-1);
	}
	open_pipefds(hold->pipegroups, pipe_fds);
	(*i) = 0;
	return (0);
}

void close_pipe_fds(int32_t pipe_fds[MAX_FD][2], int32_t i)
{
	close(pipe_fds[i][1]);
	if (i != 0)
		close(pipe_fds[i - 1][0]);
}

void wait_4_childs(t_hold *hold)
{
	int32_t i;

	i = 0;
	while (i++ < hold->pipegroups)
		waitpid(-1, &g_error_code, WUNTRACED);
}

void	executer(t_hold *hold, char **env)
{
	int32_t	i;
	t_pars	*parsed_node;
	int32_t	pipe_fds[MAX_FD][2];

	parsed_node = hold->pars_list;
	if (prep_exec(hold, pipe_fds, &i) == -1)
		return ;
	while (i < hold->pipegroups)
	{
		handle_here_doc(parsed_node);
		if (fork() == 0)
		{
			child_sig();
			redirection(parsed_node, i, hold->pipegroups, pipe_fds);
			exec_child(hold, parsed_node, env, pipe_fds);
		}
		else
			close_pipe_fds(pipe_fds, i);
		i++;
		parsed_node = parsed_node->next;
	}
	close(pipe_fds[i - 1][0]);
	wait_4_childs(hold);
}

// int32_t	prep_exec(t_hold *hold)
// {
// 	if (g_error_code != 0)
// 		return (1);
// 	if (hold->pipegroups == 1 && hold->lex_struct->macro == BUILTIN)
// 	{
// 		handle_single_builtin(hold);
// 		return (1);
// 	}
// 	return (0);
// }

// void	close_fds(int32_t i, int32_t pipe_fds[MAX_FD][2])
// {
// 	close(pipe_fds[i][1]);
// 	if (i != 0)
// 		close(pipe_fds[i - 1][0]);
// }

// void	executer_cont(t_hold *hold, char **env, int32_t i, t_pars *parsed_node)
// {
// 	int32_t	pipe_fds[MAX_FD][2];

// 	if (prep_exec(hold))
// 		return ;
// 	open_pipefds(hold->pipegroups, pipe_fds);
// 	while (i < hold->pipegroups)
// 	{
// 		if (parsed_node->here_doc_delim != NULL)
// 			handle_here_doc(parsed_node);
// 		if (fork() == 0)
// 		{
// 			child_sig();
// 			redirection(parsed_node, i, hold->pipegroups, pipe_fds);
// 			exec_child(hold, parsed_node, env, pipe_fds);
// 		}
// 		else
// 			close_fds(i, pipe_fds);
// 		i++;
// 		parsed_node = parsed_node->next;
// 	}
// 	close(pipe_fds[i - 1][0]);
// 	i = 0;
// 	while (i++ < hold->pipegroups)
// 		waitpid(-1, &g_error_code, WUNTRACED);
// }

// void	executer(t_hold *hold, char **env)
// {
// 	int32_t	i;
// 	t_pars	*parsed_node;

// 	i = 0;
// 	parsed_node = hold->pars_list;
// 	executer_cont(hold, env, i, parsed_node);
// }
