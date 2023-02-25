/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 23:45:53 by mmensing          #+#    #+#             */
/*   Updated: 2022/06/06 17:42:03 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	function erases the data in the n bytes of the memory
       		starting at the location pointed to by s, by writing zeros 
			(bytes containing '\0') to that area.
 * @param str space in memory that gets sized to null
 * @param n lengh we want to str gets nulled
 */
void	ft_bzero(void *str, size_t n)
{
	char	*ptr;
	size_t	i;

	ptr = (char *) str;
	i = 0;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
}

// int main()
// {
//     char array[30] = "plz delete dis shit";
//     printf("before mine: %s\n", array);
//     ft_bzero(array, 2);
//     printf("after mine: %s\n", array);
//     printf("before ori: %s\n", array);
//     bzero(array, 2);
//     printf("after ori: %s\n", array);
// }