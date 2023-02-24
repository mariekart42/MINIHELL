/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 19:04:22 by mmensing          #+#    #+#             */
/*   Updated: 2022/05/31 22:36:50 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	funtion searches for first occurrence of smaller string (str2)
 *			in bigger string (str1) up to the amount of len
 * 
 * @param str1 bigger string where str2 gets searched for
 * @param str2 smaller string that is getting searched in str1
 * @param len up to how many characters we are searching in str1
 * @return char* 	returns pointer to position in str if found
 * 					returns pointer to first string if second string is empty
 *					returns NULL if not found
 */
char	*ft_strnstr(const char *str1, const char *str2, size_t len)
{
	size_t	i;
	int		k;

	i = 0;
	k = 0;
	if (str2[i] == '\0')
		return ((char *)str1);
	while ((i < len) && (str1[i] != '\0'))
	{
		while (((i + k) < len) && (str2[k] == str1[k + i]))
		{
			if (str2[k + 1] == '\0')
				return ((char *) str1 + i);
			k++;
		}
		k = 0;
		i++;
	}
	return ((char *) 0);
}

// int main()
// {
//     char array1[20] = "fuck u bitch :)";
//     char array2[10] = "fuck";
//     char *ptr;
//     int size = 9;
//     ptr = ft_strnstr(array1, array2, size);
//     //ptr = strnstr(array1, array2, size);
//     printf("ptr: %s", ptr);
// } 