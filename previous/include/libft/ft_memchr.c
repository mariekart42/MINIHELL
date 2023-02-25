/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:40:02 by mmensing          #+#    #+#             */
/*   Updated: 2022/05/30 22:51:50 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	function searches for the first occurrence of the character 
			c in the first n bytes in str
 * @param str string i that c gets searched
 * @param c the character that should get found
 * @param n up to how many characters we are searching
 * @return void* 
 */
void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *) str;
	i = 0;
	while (i < n)
	{
		if (ptr[i] == (unsigned char) c)
		{
			return ((void *) ptr + i);
		}
		i++;
	}
	return ((void *) '\0');
}

// int main()
// {
//     char array[20] = "scheiss die wand an";
//     int c = 119; //w
//     char *ptr;
//     unsigned long size = 10;
//     ptr = ft_memchr(array, c, size);
//     printf("%s\n", ptr);
// }