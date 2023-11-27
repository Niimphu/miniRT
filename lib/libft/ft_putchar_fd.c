/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:00:24 by yiwong            #+#    #+#             */
/*   Updated: 2023/02/11 17:51:35 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This function outpus the character 'c' to the given file descriptor.*/

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return ;
}
