/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 21:30:47 by mmensing          #+#    #+#             */
/*   Updated: 2023/04/02 21:30:47 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sig_handle(int sig)
{
	if (sig == SIGINT)
		ft_putstr_fd(BLU"\b\b\nMINIHELL> "RESET, 1);
}

void	sig_handle_child(int sig)
{
	if (sig == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", 1);
	if (sig == SIGINT)
		ft_putchar_fd('\n', 1);
}

void	heredoc_sig_handle(int sig)
{
	if (sig == SIGINT)
		exit(1);
}
