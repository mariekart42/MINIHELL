/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:06:42 by mmensing          #+#    #+#             */
/*   Updated: 2022/05/30 21:12:43 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief 	function checks if 'val' is a alphanumeric character 
			(0-9 & a-z & A-Z)
 * 
 * @param val parameter that gets checked
 * @return 	int	returns 1 if parameter is alphanumeric
				returns 0 if not
 */
int	ft_isalnum(int val)
{
	if ((val >= 48 && val <= 57) || (val >= 65 && val <= 90) || \
		(val >= 97 && val <= 122))
		return (1);
	return (0);
}

// int main()
// {
//     int bla = 49;
//     int test;
//     test = isalnum(bla);
//     printf("ori: %d\n", test);
//     test = ft_isalnum(bla);
//     printf("mine: %d\n", test);
// }