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
