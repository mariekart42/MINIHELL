/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:40:29 by mmensing          #+#    #+#             */
/*   Updated: 2023/04/04 12:43:18 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* function checks lexed_list for any kind of 
 * syntax errors (most of them are already handeled in lexer)
 * sets global variable 'exit_code' to error return value */
int32_t	check_syntax_errors(t_hold *hold)
{
	if ((last_node_lex(hold->lex_struct))->macro == PIPE || \
		(last_node_lex(hold->lex_struct))->macro == SING_CLOSE_REDIR || \
		(last_node_lex(hold->lex_struct))->macro == SING_OPEN_REDIR || \
		(last_node_lex(hold->lex_struct))->macro == DOUBL_CLOSE_REDIR)
	{
		exit_status("syntax error near unexpected token 'newline'", "", "", 69);
		return (-1);
	}
	return (0);
}
