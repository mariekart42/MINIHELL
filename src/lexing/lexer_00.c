/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_00.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:21:24 by mmensing          #+#    #+#             */
/*   Updated: 2023/04/02 21:21:24 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int32_t	lex_word_cont(t_hold *hold, char *s, int32_t i, int32_t	x)
{
	char	*quote_chunk_;
	char	*string;
	bool	single_expand;

	quote_chunk_ = NULL;
	string = ft_calloc(ft_strlen(s) + 1, 1);
	while (1)
	{
		if (is_invalid_char(s, i))
			break ;
		else if (s[i] == 34 || s[i] == 39)
		{
			single_expand = check_single_expand(s, i);
			quote_chunk_ = quote_chunk2(s, i);
			i += update_i(quote_chunk_);
			if (quote_chunk_ != NULL)
				string = handle_quote_chunk(&string, &quote_chunk_);
			x = ft_strlen(string) - 1;
		}
		else
			string[x] = s[i];
		increase_counters(&i, &x);
	}
	when_x_positive(hold, x, string, single_expand);
	return (i - 1);
}

int32_t	lex_word(t_hold *hold, char *s, int32_t i)
{
	int32_t	x;

	x = 0;
	return (lex_word_cont(hold, s, i, x));
}

/* function adds pipe symbol as a new node to the 'lex_struct'
 * THROWS ERROR IF:
 *		- pipe at the very beginning of the line
 *		- more then one pipe symbol in a row (only seperated by spaces) */
void	lex_pipe(t_hold *hold, int32_t i)
{
	if (i == 0)
		return (exit_status("syntax error near unexpected token '|'", ""\
																	, "", 2));
	i++;
	while (hold->line[i] == ' ')
		i++;
	if (hold->line[i] == '|')
		return (exit_status("syntax error near unexpected token '|'", ""\
																	, "", 2));
	add_node_lex(hold, "|");
}

void	check_closed_quotes(t_hold *hold)
{
	char	quote;
	int32_t	i;

	i = 0;
	while (hold->line[i] != '\0')
	{
		if (hold->line[i] == 34 || hold->line[i] == 39)
		{
			quote = hold->line[i];
			i++;
			while (hold->line[i] != quote)
			{
				if (hold->line[i] == '\0')
					return (exit_status("syntax error: quotes are unclosed!"\
																, "", "", 69));
				i++;
			}
		}
		i++;
	}
}

// devide chunks of commands etc in single linked list
void	lexer(t_hold *hold)
{
	int32_t	i;

	i = 0;
	check_closed_quotes(hold);
	while (hold->line[i] != '\0' && hold->line[i] != '\n')
	{
		if (g_error_code != 0)
			return ;
		if (hold->line[i] == '|')
			lex_pipe(hold, i);
		else if (hold->line[i] == '<' || hold->line[i] == '>')
			i = lex_redir(hold, i);
		else if (hold->line[i] != ' ' && hold->line[i] != '\t')
			i = lex_word(hold, hold->line, i);
		i++;
	}
}
