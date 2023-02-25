/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 18:54:20 by mmensing          #+#    #+#             */
/*   Updated: 2022/06/06 17:42:15 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief   function checks if parameter is a digit (0 - 9)
 * 
 * @param val parameter that gets checked
 * @return int  returns 1 if parameter is a digit
                returns 0 if not
 */
int	ft_isdigit(int val)
{
	if (val >= 48 && val <= 57)
	{
		return (1);
	}
	return (0);
}

/* int main()
{
    int bla = 50;
    int test;
    test = ft_isdigit(bla);
    printf("%d\n", test);
    test = ft_isdigit(bla);
    printf("%d\n", test);
}
 */
