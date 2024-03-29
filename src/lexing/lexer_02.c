/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_02.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:21:29 by mmensing          #+#    #+#             */
/*   Updated: 2023/04/02 21:21:29 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_string(char *line, int32_t i, int32_t quote_len_)
{
	int32_t	x;
	char	*string;
	char	quote;

	x = 0;
	string = (char *)malloc(quote_len_ + 1);
	quote = line[i];
	i++;
	while (line[i] != '\0')
	{
		if (line[i] == quote)
			break ;
		string[x] = line[i];
		x++;
		i++;
	}
	if (x <= 0)
		return (NULL);
	string[x] = '\0';
	return (string);
}

char	*handle_quote_chunk(char **string, char **quote_chunk)
{
	char	*tmp;

	tmp = ft_strjoin(*string, *quote_chunk);
	free(*string);
	*string = ft_strdup(tmp);
	free(tmp);
	free(*quote_chunk);
	tmp = NULL;
	quote_chunk = NULL;
	return (*string);
}

int32_t	update_i(char *quote_chunk)
{
	if (quote_chunk == NULL)
		return (1);
	else
		return (ft_strlen(quote_chunk) + 1);
}

char	*quote_chunk2(char *line, int32_t i)
{
	char	quote;
	int32_t	quote_len_;

	quote = line[i];
	quote_len_ = quote_len(line, i + 1, quote);
	if (line[i + 1] == quote || quote_len_ == -1)
		return (NULL);
	return (init_string(line, i, quote_len_));
}

bool	check_single_expand(char *s, int32_t i)
{
	if (s[i] == '\'' && s[i + 1] == '$' && s[i + 2] != '\0')
		return (true);
	else
		return (false);
}
