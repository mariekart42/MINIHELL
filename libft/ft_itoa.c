/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 17:31:07 by mmensing          #+#    #+#             */
/*   Updated: 2022/05/30 21:32:23 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief converting integer into string
 * 
 * @param n integer that gets convertet
 * @return char pointer to string
 */
static int	len_func(int n)
{
	int		i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*converting(int len, int p, char *ptr, int n)
{
	while (len + 1 > p)
	{
		if (n < 0)
			ptr[len] = n % 10 * (-1) + '0';
		else
			ptr[len] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		len;
	int		p;

	len = 0;
	len = len_func(n);
	ptr = (char *) malloc (len + 1);
	if (!ptr)
		return (NULL);
	p = 0;
	if (n < 0)
	{
		ptr[0] = '-';
		p = 1;
	}
	ptr[len] = '\0';
	len--;
	return (converting(len, p, ptr, n));
}

// int main()
// {
// 	int num = -2304;
// 	char *ptr;
// 	ptr = ft_itoa(num);
// 	printf("ptr: %s\n", ptr);
// }