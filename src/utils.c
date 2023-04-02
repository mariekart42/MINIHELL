/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:40:33 by mmensing          #+#    #+#             */
/*   Updated: 2023/04/02 21:42:15 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	- - - -  for LEX struct  - - - - - - - - - - - - - - 
/* function adds node at the end of 'lex_struct'
 * checks if list is NULL -> appends node at the beginning			*/
void	add_node_lex(t_hold *hold, char *content)
{
	t_lex	*ptr;

	ptr = (t_lex *)malloc(sizeof(t_lex));
	ptr->item = ft_strdup(content);
	ptr->next = NULL;
	if (hold->lex_struct == NULL)
		hold->lex_struct = ptr;
	else
		(last_node_lex(hold->lex_struct))->next = ptr;
}

t_lex	*last_node_lex(t_lex *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

t_pars	*last_node_pars(t_pars *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*
Appends a string to a string array.
If the string array doesn't exist yet,
makes a new string array with the string as only content.
Frees the passed string array.
Danger! The intended use case is narrow. You might end up freeing stuff
you intended to keep.
It should mostly only be used for one and the same array.
Ok:				array_a = append_string(array_a, string);
Probably bad:	array_b = append_string(array_a, string);
It won't leak, but array_a is lost.
*/
char	**append_string(char **array, char *string)
{
	char	**result;
	int		i;

	if (!array)
	{
		result = malloc(2 * sizeof(char *));
		result[0] = string;
		result[1] = NULL;
		return (result);
	}
	i = 0;
	while (array[i])
		i++;
	result = malloc((i + 2) * sizeof(char *));
	i = 0;
	while (array[i])
	{
		result[i] = array[i];
		i++;
	}
	result[i] = string;
	i++;
	result[i] = NULL;
	free(array);
	return (result);
}

bool	only_spaces(char *line)
{
	int32_t	i;

	i = 0;
	if (line[skip_spaces(line, i)] == '\0')
		return (true);
	else
		return (false);
}
