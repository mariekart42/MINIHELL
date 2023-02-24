/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:24:52 by mmensing          #+#    #+#             */
/*   Updated: 2022/06/06 17:42:12 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function checks if 'val' is a ASCII character (-1 [0 to 127] 128)
 * 
 * @param val parameter that gets checked
 * @return int  returns 1 if parameter is ASCII
                returns 0 if not
 */
int	ft_isascii(int val)
{
	if (val >= 0 && val <= 127)
		return (1);
	return (0);
}

// int main()
// {
//     int bla = -1;
//     int test;
//     test = isascii(bla);
//     printf("ori: %d\n", test);
//     test = ft_isascii(bla);
//     printf("mine: %d\n", test);
// }