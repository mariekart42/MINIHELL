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
