/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 01:29:03 by mmensing          #+#    #+#             */
/*   Updated: 2022/06/06 22:53:58 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"// 3/3 tester good

/**
 * @brief   copies up to dstsize - 1 characters from the string src to dst
 *          gets null-terminated
 *          If src and dst strings overlap, the behavior is undefined
 * 			function does not check if dts or src is NULL !
 * @param dst 
 * @param src 
 * @param size len that gets copied(NULL should already be included)
 * @return size_t   total len of string function tried to create
 */
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	counter;

	i = 0;
	counter = 0;
	while (src[counter] != '\0')
	{
		counter++;
	}
	if (size == 0)
	{
		return (counter);
	}
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (counter);
}

// int main(void)
// {
//     char    dst[14] = "3a";
//     char    src[16] = "lorrem";
//     size_t    n = 6;
//      size_t val;
//      //val = strlcpy(dst, src, n);
//      val = ft_strlcpy(dst, src, n);
//      printf("val: %zu\n", val);
// } 