/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 14:44:32 by mmensing          #+#    #+#             */
/*   Updated: 2022/05/30 21:12:33 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function checks if 'val' is a alphabetic character (a-z & A-Z)
 * 
 * @param val parameter that gets checked
 * @return int	int returns 1 if parameter is alphanumeric
				returns 0 if not
 */
int	ft_isalpha(int val)
{
	if ((val >= 65 && val <= 90) || (val >= 97 && val <= 122))
	{
		return (1);
	}
	return (0);
}

// int main(void)
// {
//     int beer = 'c';
//     int para;
//     int yee;
//     para = ft_isalpha(beer);
//     printf("mine: %d\n", para);
//     yee = isalpha(beer);
//     printf("ori: %d\n", yee);
// }