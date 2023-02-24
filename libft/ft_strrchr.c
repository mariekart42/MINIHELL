/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 19:24:08 by mmensing          #+#    #+#             */
/*   Updated: 2022/05/31 22:39:42 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief   function searches for the LAST occurrence in str for character c
 *          if str doesnt end with NUL program might crash lol
 * @param str string where c gets searched for
 * @param c character that gets searched in str
 * @return char*    returns pointer to the character if found 
                    (pointer points to the place where founc c in str)
                    returns NULL if not found
 */
char	*ft_strrchr(const char *str, int c)
{
	int	k;

	k = 0;
	while (str[k] != '\0')
		k++;
	while (k >= 0)
	{
		if (str[k] == (char) c)
		{
			return ((char *) str + k);
		}
		k--;
	}
	return ((char *) '\0');
}

// int main()
// {
//     //char no_array[20] = "brezelsosse";
//     char yes_array[30] = "raa death is nice lol";
//     int c = 100;
//     char *ptr;
//     ptr = ft_strrchr(yes_array, c);
//     //ptr = strchr(yes_array, c);
//     printf("ptr: %s\n", ptr);
// }