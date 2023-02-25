/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:24:05 by mmensing          #+#    #+#             */
/*   Updated: 2022/05/30 23:02:52 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	function copies src into dest 
			no NULL at the end
			function doesn’t check for overflow or \0 
 * @param dest pointer where stuff gets copied to
 * @param src stuff that gets copied into dest
 * @param n up to how many characters gets copy pasted
 * @return void* dest
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*sr;
	char	*des;
	size_t	i;

	sr = (char *) src;
	des = (char *) dest;
	i = -1;
	if ((src != NULL) || (dest != NULL))
	{
		while (++i < n)
		{
			des[i] = sr[i];
		}
	}
	return (des);
}

// int main()
// {
//     char array1[20] = "du bist behindert";
//     char array2[10];
//     unsigned int size = 10;
//     ft_memcpy(array2, array1, size);
//     printf("mine dest: %s\n", array2);
//     memcpy(array2, array1, size);
//     printf("ori dest: %s\n", array2);
// }
