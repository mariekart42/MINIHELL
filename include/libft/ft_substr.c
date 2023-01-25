/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 00:03:01 by mmensing          #+#    #+#             */
/*   Updated: 2022/05/31 22:45:24 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function allocates (with malloc) and returns a substring
 *        from the string s
 *        substring begins at start and ends with len
 * @param s string where a subtring gets excluded of
 * @param start start of created substring 
 * @param len end of created substring
 * @return char pointer to allocated mem with subtring
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*newstr;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if ((unsigned int)ft_strlen(s) < len)
		len = ft_strlen(s);
	newstr = malloc(sizeof (char) * (len + 1));
	if (!(newstr))
		return (NULL);
	newstr = ft_memcpy(newstr, (char *)(s + start), len);
	newstr[len] = '\0';
	return (newstr);
}

// int main()
// {
//      char array[50] = "bro something wrong with you";
//      unsigned int start = 3;
//      size_t end = 10;
//      char *ptr1;
//      ptr1 = ft_substr(array, start, end);
//      printf("subtring: %s\n", ptr1);
// }