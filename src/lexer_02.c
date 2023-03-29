#include "minishell.h"

char	*init_string(char *line, char quote, int32_t i, int32_t quote_len_)
{
	int32_t	x;
	char	*string;

	x = 0;
	string = (char *)malloc(quote_len_ + 1);
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
	quote_len_ = quote_len(line, i+1, quote);
	if (line[i + 1] == quote || quote_len_ == -1)
		return (NULL);
	return (init_string(line, quote, i, quote_len_));
}
