/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/16 18:58:02 by mmensing          #+#    #+#             */
/*   Updated: 2022/06/06 23:20:01 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief 	function calls function f that allocates space for each 
 *			character of strins s passed to strmapi, 
 *			and returns char pointer to it
 * @param s string of characters
 * @param f function that allocates mem for each character of string s
 * @return char 	returns pointer to created array of pointers
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ptr;
	int		i;

	if (!s)
		return (NULL);
	ptr = (char *) malloc (ft_strlen((char *)s) + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// int main()
// {
// 	char array[] = "pimpaliukas";
// 	char *ptr;
// 	ptr = ft_strmapi(array, f);
// 	printf("ptr: %s\n", ptr);
// }