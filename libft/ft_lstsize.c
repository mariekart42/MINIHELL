/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 20:22:29 by mmensing          #+#    #+#             */
/*   Updated: 2022/06/06 17:42:33 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Counts the number of nodes in a list.
 * 
 * @param lst The beginning of the list.
 * @return int The length of the list
 */
int	ft_lstsize(t_list *lst)
{
	t_list	*new_node;
	int		i;

	i = 0;
	new_node = NULL;
	new_node = lst;
	while (new_node != NULL)
	{
		new_node = new_node->next;
		i++;
	}
	return (i);
}

// int main()
// {
// 	t_list *val = NULL;
// 	int i = 0;
// 	i = ft_lstsize(val);
// 	printf("i: %d\n", i);
// }