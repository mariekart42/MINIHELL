/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 13:49:46 by mmensing          #+#    #+#             */
/*   Updated: 2022/06/08 14:01:16 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief   function copies str2(str2) into dest(str1) array
            does not check the validity of the destination buffer
            copies the data first to an intermediate buffer, then from the 
            buffer to destination
            -> similar to memcpy but better
			one of dst or src can be NULL but not both!
 * @param str1 destination string
 * @param str2 str2 string
 * @param n up to how many characters get copied 
 * @return void* 
 */

void	rev_func(size_t i, size_t n, char *st1, char *st2)
{
	while (i < n)
	{
		st1[i] = st2[i];
		i++;
	}
}

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	size_t	i;
	int		rev_i;
	char	*st1;
	char	*st2;

	if (!str1 && !str2)
		return (NULL);
	i = 0;
	rev_i = n - 1;
	st1 = (char *)str1;
	st2 = (char *)str2;
	if (str1 < str2)
	{
		rev_func(i, n, st1, st2);
		return (str1);
	}
	while (i++ < n)
	{
		st1[rev_i] = st2[rev_i];
		rev_i--;
	}
	return (str1);
}

// int main()
// {
//     char str2[30] = "stol z powylamywanymi nogami";
//     char dest[20] = "a";
//     //printf("before: %s\n", dest);
//     ft_memmove(dest, str2, 18);
//     printf("after: %s\n", dest);
//     char str22[30] = "stol z powylamywanymi nogami";
//     char dest2[20] = "a";
//     memmove(dest2, str22, 18);
//     printf("memmove: %s\n", dest2);
// }