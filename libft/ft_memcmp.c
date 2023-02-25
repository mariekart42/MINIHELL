/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:52:10 by mmensing          #+#    #+#             */
/*   Updated: 2022/05/30 22:57:07 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function compares 2 strings and returns the difference
 * 
 * @param str1 first string
 * @param str2 second string
 * @param n up to how many characters we are searching
 * @return int  returns differsnce between both strings (ASCII value)
                returns 0 if they are the same 
 */
int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	unsigned char	*ptr1;
	unsigned char	*ptr2;
	size_t			c;

	ptr1 = (unsigned char *) str1;
	ptr2 = (unsigned char *) str2;
	c = 0;
	while (c < n)
	{
		if ((ptr1[c] - ptr2[c]) != 0)
			return (ptr1[c] - ptr2[c]);
		c++;
	}
	return (0);
}

// int main()
// {
//     char array1[20] = "vier ist toll";
//     char array2[20] = "bier ist fantastisch";
//     int size = 5;
//     int val;
//     val = ft_memcmp(array1, array2, size);
//     //val = memcmp(array1, array2, size);
//     printf("%d\n", val);
// } 