/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/03 16:38:22 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/miniRT.h"

#define RED "\033[1;31m"
#define RESET "\033[1;0m"

// char	*get_error_message(int error_code);

// void	error_exit(int error_code)
// {
// 	char	*error_message;

// 	write(2, RED, 8);
// 	write(2, "Error\n", 6);
// 	error_message = get_error_message(error_code);
// 	write(2, error_message, ft_strlen(error_message) * sizeof(char));
// 	write(2, RESET, 7);
// 	exit(error_code);
// }

void	ft_perror(char *message)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd("\n", 2);
	ft_putstr_fd(RESET, 2);
}
