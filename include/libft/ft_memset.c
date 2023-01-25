/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:44:58 by mmensing          #+#    #+#             */
/*   Updated: 2022/06/04 16:39:10 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	function writes len bytes of value c (converted to an unsigned char)
 			to the string b
 * 
 * @param str where the character gets copied too
 * @param c the character that gets copied to str 
 			gets convertet to ASCII (int 0 = char 48)
 * @param n how many characters gets copied to str
 * @return void* str
 */
void	*ft_memset(void *str, int c, size_t n)
{
	char	*ptr;
	size_t	i;

	ptr = (char *) str;
	i = 0;
	while (i < n)
	{
		ptr[i] = c;
		i++;
	}
	str = (void *) ptr;
	return (str);
}

// int main()
// {
//     char array[50] = "123456789 sag ich ja lol";
//     printf("befor mine: %s\n", array);
//     ft_memset(array, 'c', 5);
//     printf("after mine: %s\n", array);
//     printf("befor ori: %s\n", array);
//     memset(array, 'c', 5);
//     printf("after ori: %s\n", array);
// }  