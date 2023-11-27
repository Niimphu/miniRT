/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:17:06 by yiwong            #+#    #+#             */
/*   Updated: 2023/02/11 17:51:55 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This function outputs the string 's' to the given file descriptor. */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	while (s[0])
		ft_putchar_fd((s++)[0], fd);
	return ;
}
