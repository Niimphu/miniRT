/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:21:03 by yiwong            #+#    #+#             */
/*   Updated: 2023/02/11 17:52:29 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This function outputs the string 's' to the given file descriptor,
	followed by a newline. */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
	return ;
}
