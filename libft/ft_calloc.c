/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 21:47:21 by mmensing          #+#    #+#             */
/*   Updated: 2022/06/06 22:17:47 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	function allocates 'nitems' bytes of memory, each in size of 'size' 
 			(int, char etc)
			different to malloc, sets all places to '\0'
 * 
 * @param count 
 * @param size 
 * @return void* returns pointer to allocated memory
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*output;

	if (count >= 4294967295 || size >= 4294967295)
		return (NULL);
	output = malloc(count * size);
	if (!output)
		return (NULL);
	ft_bzero(output, count * size);
	return (output);
}

// int main()
// {
//     char *ptr;
//     char array[20] = "diese Brot gut";
//     ptr = array;
//     int val;
//     val = strlen(ptr);
//     //ptr = (char *) malloc(val * sizeof(char));
//     //ptr = (char *) calloc(val * sizeof(char),sizeof(char));
//     ptr = (char *) ft_calloc(val * sizeof(char),sizeof(char));
//     printf("%s\n", ptr);
// }