/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 12:15:50 by mmensing          #+#    #+#             */
/*   Updated: 2022/06/06 22:53:39 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"// 3/3 tester good

/**
 * @brief 	function appends whole string src at the end of dst
			take whole size of destination buffer not only the size
			garantees null termination (as long size > 0 && dest has at 
			least one free space)
			function does not check if dts or src is NULL !
 * 
 * @param dst string where src gets appended to
 * @param src string that gets appended to the end of dst 
 * @param len how many characters of dst gets appended
 * @return size_t	returns size of src + dst (without NUL)
					returns NULL if fails
 */
size_t	ft_strlcat(char *dst, const char *src, size_t len)
{
	char		*d;
	const char	*s;
	size_t		i;
	size_t		d_len;

	d = dst;
	s = (char *) src;
	i = len;
	d_len = 0;
	while ((i-- != 0) && (*d != '\0'))
		d++;
	d_len = d - dst;
	i = len - d_len;
	if (i == 0)
		return (d_len + ft_strlen(s));
	while (*s != '\0')
	{
		if (i != 1)
			ft_strlcpy (d++, s, i--);
		s++;
	}
	*d = '\0';
	return (d_len + (s - src));
}

// int main()
// {
//     char s1[]= "Moon";
//     char s2[]= "Base";
//     size_t size = 4;
//     printf("%lu\n", ft_strlcat(s1,s2,size));
//     printf("%s",s1);
// }