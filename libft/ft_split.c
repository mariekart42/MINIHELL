/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:52:16 by mmensing          #+#    #+#             */
/*   Updated: 2022/06/08 15:27:31 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates (with malloc(3)) and returns an array of strings obtained 
 * by splitting ’s’ using the character ’c’ as a delimiter. 
 * The array must end with a NULL pointer.
 * 
 * @param s The string to be split.
 * @param c The delimiter character.
 * @return The array of new strings resulting from the split.
 * NULL if the allocation fails.
 */
static char	*sub_dup(const char *str, int start, int finish)
{
	char	*word;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	word = malloc((finish - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (start < finish)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

static int	amount_subs(const char *s, char c)
{
	int		i;
	int		subs;

	if (!s)
		return (0);
	i = 0;
	subs = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			subs++;
		i++;
	}
	return (subs);
}

char	**ft_split(char const *s, char c)
{
	char	**str2;
	size_t	i;
	size_t	k;
	int		start;

	str2 = malloc((amount_subs(s, c) + 2) * sizeof(char *));
	if (!s || !str2)
		return (0);
	i = 0;
	k = 0;
	start = -1;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && start < 0)
			start = i;
		else if ((s[i] == c || i == ft_strlen(s)) && start >= 0)
		{
			str2[k] = sub_dup(s, start, i);
			start = -1;
				k++;
		}
		i++;
	}
	str2[k] = 0;
	return (str2);
}

// int main()
// {
//      char *ptr = "du bist dumm";
//      char c = ' ';
//      char **brot; 
//      brot = ft_split(ptr, c);
//      //printf("val: %s\n", brot);
//      int i = 0;
//      while (brot[i] != NULL)
//      {
//           printf("%s\n", brot[i]);
//           i++;
//      }
// }