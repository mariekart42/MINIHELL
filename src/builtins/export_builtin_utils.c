#include "minishell.h"

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	size_t		index;
	size_t		src_len;

	src_len = ft_strlen(src);
	index = 0;
	while (index < len)
	{
		if (index <= src_len)
			dest[index] = src[index];
		else
			dest[index] = '\0';
		index++;
	}
	return (dest);
}

char	*ft_strnew(const int size)
{
	int		i;
	char	*new_string;

	if (size < 0)
	{
		return (0);
	}
	i = 0;
	new_string = (char *)malloc(sizeof(char) * (size + 1));
	while (i <= size)
	{
		new_string[i] = '\0';
		i++;
	}
	return (new_string);
}

char	*ft_strndup(const char *s1, size_t n)
{
	char	*cpy;

	if (ft_strlen((char *)s1) < n)
		cpy = ft_strnew(ft_strlen((char *)s1));
	else
		cpy = ft_strnew(n);
	if (cpy == NULL)
		return (NULL);
	return (ft_strncpy(cpy, (char *)s1, n));
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	var_start_number(t_pars *parsed_node, int i)
{
	if (ft_isdigit(parsed_node->args[i][0]) != 0)
	{
		exit_status("export:", parsed_node->args[i],
			": not a valid identifier", 1);
		return (1);
	}
	return (1);
}
