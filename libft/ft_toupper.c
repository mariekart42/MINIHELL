/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 00:49:38 by mmensing          #+#    #+#             */
/*   Updated: 2022/05/31 22:48:58 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief returns given char in uppercase
 * 
 * @param c character that gets uppercase
 * @return int 	returns ASCII character in uppercase
				returns 'c' if character is not lowercase
 */
int	ft_toupper(int c)
{
	if ((c >= 97) && (c <= 122))
		return (c - 32);
	return (c);
}

// int main()
// {
//     int c = 100;
//     int val;
//     val = ft_toupper(c);
//     printf("val: %c\n", val);
// }