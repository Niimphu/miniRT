/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:26:17 by yiwong            #+#    #+#             */
/*   Updated: 2023/06/25 14:09:33 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This function outputs the integer 'n' to the given file descriptor. */

#include "libft.h"

void	ft_putnbr_write(int n, int fd)
{
	if (n)
		ft_putnbr_write(n / 10, fd);
	else
		return ;
	ft_putchar_fd(n % 10 + '0', fd);
	return ;
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == 0)
	{
		ft_putchar_fd('0', fd);
		return ;
	}
	if (n == -2147483648)
	{
		ft_putstr_fd("-2147483648", fd);
		return ;
	}
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	ft_putnbr_write(n, fd);
	return ;
}
