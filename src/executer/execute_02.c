/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_02.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:33:27 by mmensing          #+#    #+#             */
/*   Updated: 2023/04/02 21:33:49 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	else
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
