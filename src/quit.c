/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/03 16:38:22 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/miniRT.h"

int	window_closed(t_vars *mlx_data)
{
	mlx_clear_window(mlx_data->mlx, mlx_data->win);
	quit(mlx_data);
	return (0);
}

void	quit(t_vars *mlx_data)
{
	mlx_loop_end(mlx_data->mlx);
	mlx_destroy_display(mlx_data->mlx);
	free(mlx_data->mlx);
	exit(0);
}
