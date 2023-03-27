/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stena-he <stena-he@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 19:40:18 by mmensing          #+#    #+#             */
/*   Updated: 2023/03/27 20:23:31 by stena-he         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief returns lengh of str
 * 
 * @param str 
 * @return size_t lengh of str
 */
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	if(!str)
		return 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

// int main(void)
// {
//     char array[10] = "bananaboot";
//     int test;
//     test = ft_strlen(array);
//     printf("muine: %d\n", test);
// }