/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:21:53 by mmensing          #+#    #+#             */
/*   Updated: 2023/04/02 21:30:19 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* function counts and returns amount of pipegroups in 'lexed_list' */
void	count_pipegroups(t_hold *hold)
{
	t_lex	*tmp;
	int32_t	pipegroup;

	pipegroup = 1;
	tmp = hold->lex_struct;
	while (tmp != NULL)
	{
		if (tmp->macro == PIPE)
			pipegroup++;
		tmp = tmp->next;
	}
	if (pipegroup > 1000)
		exit_status("DUDE what da fuck!", "", "", 69);
	else
		hold->pipegroups = pipegroup;
}

char	*get_env_path(t_env_exp *env_node)
{
	t_env_exp	*tmp;

	tmp = env_node;
	while (tmp)
	{
		if (ft_strncmp(tmp->item, "PATH=", 4) == 0)
			return (tmp->item);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*return_valid_path(char *curr_cmd, char *valid_path, char **env_path)
{
	if (env_path)
	{
		free_env_path(env_path);
		env_path = NULL;
	}
	if (ft_strncmp(curr_cmd, "./", 2) == 0)
		valid_path = ft_strdup(curr_cmd);
	if (access(valid_path, F_OK | X_OK) != 0)
	{
		if (valid_path)
		{
			free(valid_path);
			valid_path = NULL;
		}
		return (NULL);
	}
	return (valid_path);
}

/* function appends command from 'pars_list' at the end of
 * each path of $PATH and checks for access
 * in case of access, function returns path
 * otherwise returns NULL		*/
char	*get_cmdpath(t_env_exp *env_node, char *curr_cmd)
{
	char	**env_path;
	char	*valid_path;
	char	*tmp;
	int32_t	i;

	tmp = NULL;
	env_path = ft_split(get_env_path(env_node), ':');
	valid_path = NULL;
	i = 0;
	while (env_path && env_path[i] != NULL)
	{
		tmp = ft_strjoin(env_path[i], "/");
		valid_path = ft_strjoin(tmp, curr_cmd);
		free(tmp);
		tmp = NULL;
		if (access(valid_path, F_OK | X_OK) == 0)
			break ;
		free(valid_path);
		valid_path = NULL;
		i++;
	}
	return (return_valid_path(curr_cmd, valid_path, env_path));
}

void	add_node_pars(t_hold **hold)
{
	t_pars	*tmp;

	tmp = (t_pars *)malloc(sizeof(t_pars));
	tmp->args = NULL;
	tmp->cmd_path = NULL;
	tmp->next = NULL;
	tmp->here_doc_delim = NULL;
	tmp->infile = STDIN_FILENO;
	tmp->outfile = STDOUT_FILENO;
	if ((*hold)->pars_list == NULL)
		(*hold)->pars_list = tmp;
	else
		(last_node_pars((*hold)->pars_list))->next = tmp;
}
