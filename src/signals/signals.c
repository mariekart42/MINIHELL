/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:30:49 by mmensing          #+#    #+#             */
/*   Updated: 2023/04/02 21:30:49 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handle);
}

void	child_sig(void)
{
	signal(SIGQUIT, sig_handle_child);
	signal(SIGINT, sig_handle_child);
}

void	heredoc_sig(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, heredoc_sig_handle);
}
