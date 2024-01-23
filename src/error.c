/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/23 16:03:19 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

#define RED "\033[1;31m"
#define RESET "\033[1;0m"

int	error(char *message)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(RESET, 2);
	return (FAIL);
}
