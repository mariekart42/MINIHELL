/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_01.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:21:26 by mmensing          #+#    #+#             */
/*   Updated: 2023/04/02 21:21:26 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* function skips all spaces and returns new index i			*/
int32_t	skip_spaces(char *str, int32_t i)
{
	while (str[i] == 32)
		i++;
	return (i);
}

int32_t	check_out_redir_syntax(t_hold **hold, int32_t i)
{
	i++;
	i = skip_spaces((*hold)->line, i);
	if ((*hold)->line[i] == '<')
		return (exit_status("syntax error near unexpected token '<'", "", "", \
																	69), -1);
	if ((*hold)->line[i] == '>')
	{
		add_node_lex((*hold), ">>");
		i++;
		i = skip_spaces((*hold)->line, i);
		if ((*hold)->line[i] == '>' || (*hold)->line[i] == '<')
			return (exit_status("syntax error near unexpected token '>'", "", \
																"", 69), -1);
		return (i - 1);
	}
	add_node_lex((*hold), ">");
	return (i - 1);
}

int32_t	check_in_redir_syntax(t_hold **hold, int32_t i)
{
	i++;
	i = skip_spaces((*hold)->line, i);
	if ((*hold)->line[i] == '<')
	{
		add_node_lex((*hold), "<<");
		i++;
		i = skip_spaces((*hold)->line, i);
		if ((*hold)->line[i] == '<')
			return (exit_status("syntax error near unexpected token '<'", "", \
																"", 69), -1);
		return (i - 1);
	}
	add_node_lex((*hold), "<");
	return (i - 1);
}

/* function checks if there are no more signs beside space and redirection sign	
 * it's an syntax error if there is nothing but redirection signs 
 * returns -1 if there is an illegal redirection sign
 * returns  0 if everything is noice        */
int32_t	check_beginning_redir(t_hold *hold)
{
	int32_t	i;

	i = 0;
	while (hold->line[i] != '\0' && hold->line[i] != '\n')
	{
		if (hold->line[i] != 32 && hold->line[i] != '<' && hold->line[i] != '>')
			return (0);
		i++;
	}
	exit_status("syntax error near unexpected token 'newline'", "", "", 2);
	return (-1);
}

/* function adds redirection symbol(s) as a new node to the 'lex_struct'
 * THROWS ERROR IF:
 *		- redir sign at the very beginning and nothing else (except spaces)
 *		- same symbol more then 2 times in a row (eg. >>>, > > >, >> >)
 *		- in any case this syntax: '><'	(eg. ><, <><, >><)				*/
int32_t	lex_redir(t_hold *hold, int32_t i)
{
	if ((i == 0) && (check_beginning_redir(hold) != 0))
		return (-1);
	if (hold->line[i] == '<')
		return (check_in_redir_syntax(&hold, i));
	else if (hold->line[i] == '>')
		return (check_out_redir_syntax(&hold, i));
	else
		return (69);
}
