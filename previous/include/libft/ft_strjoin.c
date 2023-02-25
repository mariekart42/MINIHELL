/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 01:27:29 by mmensing          #+#    #+#             */
/*   Updated: 2022/06/06 23:15:08 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function connects to given strings and allocates
 * memory for them with malloc
 * 
 * @param s1 fist string
 * @param s2 second string
 * @return char pointer to allocated memory space
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	int		i;
	int		k;

	if (!s1 || !s2)
		return (NULL);
	ptr = (char *) malloc(ft_strlen((char *)s1) + ft_strlen((char *)s2) + 1);
	if (!ptr)
		return (NULL);
	k = 0;
	i = 0;
	while (s1[i] != '\0')
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2[k] != '\0')
	{
		ptr[i] = s2[k];
		i++;
		k++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// int main()
// {
// 	char array1[30] = "du";
// 	char array2[30] = "hu";
// 	char *bla;
// 	printf("srtlen: %d\n", ft_strlen(array1) + ft_strlen(array2));

// 	bla = ft_strjoin(array1, array2);
// 	printf("ptr: %s\n", bla);
// }