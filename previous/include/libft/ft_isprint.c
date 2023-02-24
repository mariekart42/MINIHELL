/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:33:53 by mmensing          #+#    #+#             */
/*   Updated: 2022/05/30 21:19:53 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function checks if given parameter is printable (ASCII 32 - 126)
 * 
 * @param val parameter that gets checked
 * @return int  returns 1 if character is printable
                returns 0 if not
 */
int	ft_isprint(int val)
{
	if (val >= 32 && val <= 126)
		return (1);
	return (0);
}

// int main()
// {
//     int bla = 31;
//     int test;
//     test = isprint(bla);
//     printf("ori: %d\n", test);
//     test = ft_isprint(bla);
//     printf("mine: %d\n", test);
// }