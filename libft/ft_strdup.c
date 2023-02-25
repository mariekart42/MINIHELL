/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:27:56 by mmensing          #+#    #+#             */
/*   Updated: 2022/06/06 22:41:39 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief function duplicates a string and return a pointer pointing to the 
 * first byte of copied string 
 * memory reserved with malloc
 * 
 * @param src pointer to string that gets copied
 * @return char* 
 */
char	*ft_strdup(char *src)
{
	int		size;
	char	*ptr;
	int		i;

	i = 0;
	size = ft_strlen(src) + 1;
	ptr = (char *) malloc(size * sizeof(char));
	if (!ptr)
		return (NULL);
	while (src[i] != '\0')
	{
		ptr[i] = src[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// int main(void)
// {
//      char      *pointer;
//      char array[30] = "pls kill- ähh copy me";
//      pointer = ft_strdup (array);
//      printf ("%s\n", pointer);
//      printf ("%s\n", array);
// }