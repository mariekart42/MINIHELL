/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 13:55:27 by mmensing          #+#    #+#             */
/*   Updated: 2022/05/31 00:56:51 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	if (!s || !f)
		return ;
	i = 0;
	while (s[i] != '\0')
	{
		f(i, s + i);
		i++;
	}
}

// char *f(unsigned int n, char c)
// {
// 	char *ptr2;
// 	ptr2 = (char *) malloc(2);
// 	ptr2[0] = c;
// 	ptr2[1] = '\0';
// 	return(ptr2);
// }
// int main()
// {
// 	char array[] = "pimpes";
// 	char *ptr;
// 	ptr = ft_strmapi(array, f);
// 	printf("ptr: %s\n", ptr);
// }