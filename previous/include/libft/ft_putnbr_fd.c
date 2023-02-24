/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmensing <mmensing@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:08:16 by mmensing          #+#    #+#             */
/*   Updated: 2022/05/30 23:37:25 by mmensing         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Outputs the integer ’n’ to the given file descriptor
 * 
 * @param n given int to output
 * @param fd file descriptor where to write on
 */
void	ft_putnbr_mod(int nb, int fd)
{
	if (nb == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		write (fd, "-", 1);
		nb *= -1;
	}
	if (nb > 9)
	{
		ft_putnbr_mod (nb / 10, fd);
		ft_putnbr_mod (nb % 10, fd);
	}
	if (nb <= 9)
	{
		nb = nb + '0';
		write (fd, &nb, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	ft_putnbr_mod(n, fd);
}

// int main(void)
// {
//      int n = 2434;
//      ft_putnbr_fd(n);
// }