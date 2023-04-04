/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_struct_cont.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:40:12 by mmensing          #+#    #+#             */
/*   Updated: 2023/04/04 12:42:31 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_data(t_env_exp *export_list)
{
	char	*tmp_item;

	tmp_item = export_list->item;
	export_list->item = export_list->next->item;
	export_list->next->item = tmp_item;
}
