/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:38:03 by mmensing          #+#    #+#             */
/*   Updated: 2022/06/06 17:46:22 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
compares 2 char arrays if one of them is greater, less or equal
stop point is a fixed variable n
for extendet ascii using unsigned char
e.g. 
"abc" > "aba"   ->    returns 1
  ""  =  ""     ->    returns 0
 "a"  < "abc"   ->    returns -1
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((i < n) && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)(s1[i]) - ((unsigned char)s2[i]));
		}
	i++;
	}
	return (0);
}

// int main()
// {
//     const char array1[] = "trstr\200";
//     const char array2[] = "testa\0";
//     size_t size = 9;
//     int b;
//     b = ft_strncmp(array1, array2, size);
//     if (b == -1)
//         printf("array1 is less than array2\n");
//     else if (b == 1)
//         printf("array1 is more than array2\n");
//     else 
//         printf("they equal\n"); 
//      if(strncmp(array1, array2, size) < 0)
//         printf("array1 is less than array2\n");
//     else if(strncmp(array1, array2, size) > 0)
//         printf("array1 is more than array2\n");
//     else
//         printf("they equal\n");   
// }