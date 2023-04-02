/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_00.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:31:26 by mmensing          #+#    #+#             */
/*   Updated: 2023/04/02 21:40:02 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_child(t_hold *hold, t_pars *pars_node,
			int32_t pipe_fds[MAX_FD][2])
{
	close_fds_child(hold, hold->pipegroups, pipe_fds);
	if (builtin(hold, pars_node) == false)
	{
		execute_cmd(pars_node, hold->my_env);
		exit(122);
	}
	exit(g_error_code);
}

int32_t	prep_exec(t_hold *hold, int32_t pipe_fds[MAX_FD][2], int32_t *i)
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

void	close_pipe_fds(int32_t pipe_fds[MAX_FD][2], int32_t i)
{
	close(pipe_fds[i][1]);
	if (i != 0)
		close(pipe_fds[i - 1][0]);
}

void	wait_4_childs(t_hold *hold)
{
	int32_t	i;

	i = 0;
	while (i++ < hold->pipegroups)
		waitpid(-1, &g_error_code, WUNTRACED);
}

void	executer(t_hold *hold)
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
			exec_child(hold, parsed_node, pipe_fds);
		}
		else
			close_pipe_fds(pipe_fds, i);
		i++;
		parsed_node = parsed_node->next;
	}
	close(pipe_fds[i - 1][0]);
	wait_4_childs(hold);
}
