/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_03.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:21:31 by mmensing          #+#    #+#             */
/*   Updated: 2023/04/02 21:21:31 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_letter(char *pointer, char letter)
{
	int32_t	i;
	char	*return_pointer;

	i = 0;
	return_pointer = (char *)malloc(ft_strlen(pointer) + 2);
	while (pointer[i] != '\0')
	{
		return_pointer[i] = pointer[i];
		i++;
	}
	return_pointer[i] = letter;
	i++;
	return_pointer[i] = '\0';
	free(pointer);
	pointer = NULL;
	return (return_pointer);
}

int32_t	quote_len(char *line, int32_t i, char quote)
{
	int32_t	len;

	len = 0;
	while (line[i] != '\0')
	{
		if (line[i] == quote)
			return (len);
		len++;
		i++;
	}
	return (-1);
}

bool	is_invalid_char(char *s, int32_t i)
{
	if (s[i] == '\0' || s[i] == ' ' || s[i] == '|' || s[i] == '>'
		|| s[i] == '<')
	{
		return (true);
	}
	return (false);
}

void	when_x_positive(t_hold *hold, int32_t x, char *string,
			bool single_expand)
{
	t_lex	*tmp;

	if (x > 0)
	{
		string[x] = '\0';
		add_node_lex(hold, string);
		if (single_expand == true)
		{
			tmp = last_node_lex(hold->lex_struct);
			tmp->macro = DO_NOT_EXPAND;
		}
		free(string);
	}
}

void	increase_counters(int32_t *i, int32_t *x)
{
	(*i)++;
	(*x)++;
}
