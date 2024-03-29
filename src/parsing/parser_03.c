/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_03.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:21:56 by mmensing          #+#    #+#             */
/*   Updated: 2023/04/02 21:21:56 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	builtin_parser(char *node)
{
	if (ft_strncmp(node, "echo\0", 5) == 0)
		return (true);
	else if (ft_strncmp(node, "pwd\0", 4) == 0)
		return (true);
	else if (ft_strncmp(node, "unset\0", 6) == 0)
		return (true);
	else if (ft_strncmp(node, "env\0", 4) == 0)
		return (true);
	else if (ft_strncmp(node, "export\0", 7) == 0)
		return (true);
	else if (ft_strncmp(node, "cd\0", 3) == 0)
		return (true);
	else if (ft_strncmp(node, "exit\0", 5) == 0)
		return (true);
	else
		return (false);
}

/* function appends specific macro to each node of 'lex_struct'
 * 	Macros: QUOTES, PIPE, (SINGLE-/DOUBLE) REDIRECTION, BUILTIN */
void	recognize_type_cont(t_lex *tmp)
{
	while (tmp != NULL)
	{
		if (builtin_parser(tmp->item) == true)
			tmp->macro = BUILTIN;
		else if (tmp->macro == DO_NOT_EXPAND)
			return ;
		else if (ft_strncmp(tmp->item, "|", 1) == 0)
			tmp->macro = PIPE;
		else if (ft_strncmp(tmp->item, "'", 1) == 0)
			tmp->macro = SING_QUOTE;
		else if (ft_strncmp(tmp->item, "\"", 1) == 0)
			tmp->macro = DOUBL_QUOTE;
		else if (ft_strncmp(tmp->item, "<<", 2) == 0)
			tmp->macro = DOUBL_OPEN_REDIR;
		else if (ft_strncmp(tmp->item, ">>", 2) == 0)
			tmp->macro = DOUBL_CLOSE_REDIR;
		else if (ft_strncmp(tmp->item, "<", 1) == 0)
			tmp->macro = SING_OPEN_REDIR;
		else if (ft_strncmp(tmp->item, ">", 1) == 0)
			tmp->macro = SING_CLOSE_REDIR;
		else
			tmp->macro = WORD;
		tmp = tmp->next;
	}
}

void	recognize_type(t_hold *hold)
{
	t_lex	*tmp;

	tmp = hold->lex_struct;
	recognize_type_cont(tmp);
}

/* function checks and returns outfile on success
 * opens/creates file if it not exists */
int32_t	init_outfile(t_lex *file_node, int32_t type)
{
	int32_t	file_id;

	file_id = 1;
	if (type != SING_CLOSE_REDIR && type != DOUBL_CLOSE_REDIR)
		return (1);
	if (type == SING_CLOSE_REDIR)
		file_id = open(file_node->item, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == DOUBL_CLOSE_REDIR)
		file_id = open(file_node->item, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (file_id < 0)
		exit_status("Error!: unable to open outfile!", "", "", 69);
	return (file_id);
}

/* function checks and returns infile on success
 * input file must exist and be readable by the user running the command
 * file_node is the current node in pars_list	*/
int32_t	init_infile(t_pars *p_file_node, t_lex *l_file_node, int32_t type)
{
	int32_t	file_id;

	file_id = 0;
	if (type == SING_OPEN_REDIR)
	{
		file_id = open(l_file_node->item, O_RDONLY);
		p_file_node->here_doc_delim = NULL;
	}
	else if (type == DOUBL_OPEN_REDIR)
	{
		file_id = open("tmp.hd", O_WRONLY | O_CREAT, 0777);
		p_file_node->here_doc_delim = ft_strdup(l_file_node->item);
	}
	if (file_id < 0)
		exit_status(l_file_node->item, ": no such file/directory", "", 69);
	return (file_id);
}
