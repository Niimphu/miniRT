/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/03 16:38:22 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/miniRT.h"

int	key_pressed(int keycode, t_vars *mlx_data)
{
	if (keycode == XK_Escape)
	{
		mlx_clear_window(mlx_data->mlx, mlx_data->win);
		mlx_destroy_window(mlx_data->mlx, mlx_data->win);
		quit(mlx_data);
	}
	return (0);
}
