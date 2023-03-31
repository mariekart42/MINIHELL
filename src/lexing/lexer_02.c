#include "minishell.h"

// void init_lex_macro(t_hold *hold, char quote)
// {
// 	t_lex *tmp;

// 	tmp = last_node_lex(hold->lex_struct);
// 	if (quote == '\'')
// 		tmp->macro = SING_QUOTE;
// 	else if (quote == '\"')
// 		tmp->macro = DOUBL_QUOTE;

// }

char	*init_string(t_hold *hold, char *line, int32_t i, int32_t quote_len_)
{
	int32_t	x;
	char	*string;
	char quote;

	x = 0;
	string = (char *)malloc(quote_len_ + 1);
	quote = line[i];
	i++;
	// init_lex_macro(hold, quote);
	// at last node of lex list add macro single or double quote
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

char	*quote_chunk2(t_hold *hold, char *line, int32_t i)
{
	char	quote;
	int32_t	quote_len_;

	quote = line[i];
	quote_len_ = quote_len(line, i + 1, quote);
	if (line[i + 1] == quote || quote_len_ == -1)
		return (NULL);
	return (init_string(hold, line, i, quote_len_));
}
