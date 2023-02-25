/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 17:12:21 by mmensing          #+#    #+#             */
/*   Updated: 2022/06/08 13:46:33 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	allocates (with malloc) and returns a copy of s1 with the parts
 *			removed that are the same as the characters in set in the beginning
 *			and in the end
 * @param s1 string that gets modiefied 
 * @param set string that gets removed in s1
 * @return char	returns pointer to copy of s1 with excluded parts (set) at
 				beginning and end
 */
static char	*end_cut_func(char *s2, char *set2)
{
	char	*ptr;
	int		p;
	int		len_s2;

	ptr = NULL;
	p = 0;
	len_s2 = ft_strlen(s2);
	while (len_s2 >= 0)
	{
		if (ft_strchr(set2, s2[len_s2]) == (char *) '\0')
		{
			ptr = ft_strdup(s2);
			while (len_s2 >= 0)
			{
				ptr[p] = s2[p];
				p++;
				len_s2--;
			}
			ptr[p] = '\0';
			return (ptr);
		}
		len_s2--;
	}
	return (s2);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	char	*ptr2;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	ptr2 = NULL;
	while (s1[i] != '\0')
	{
		if (ft_strchr(set, s1[i]) == (char *) '\0')
		{
			return (end_cut_func((char *)s1 + i, (char *)set));
		}
		i++;
	}
	ptr2 = (char *) malloc(1);
	if (!ptr2)
		return (NULL);
	*ptr2 = '\0';
	return (ptr2);
}

// int main()
// {
// 	char array[] = "tripouille   xxx";
// 	char array2[] = "x";
// 	char *bla;
// 	bla = ft_strtrim(array, array2);
// 	printf("bla: %s\n", bla);
// }