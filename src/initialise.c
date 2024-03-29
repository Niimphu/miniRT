/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/04 16:16:41 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static void	create_window(t_vars *mlx_data);

int	initialise(t_rt *rt)
{
	rt->mlx_data = ft_calloc(1, sizeof(t_vars));
	if (!rt->mlx_data)
		return (FAIL);
	rt->mlx_data->mlx = mlx_init();
	create_window(rt->mlx_data);
	return (0);
}

static void	create_window(t_vars *mlx_data)
{
	mlx_data->win_x = SCREEN_WIDTH;
	mlx_data->win_y = SCREEN_HEIGHT;
	mlx_data->aspect_ratio = (double)mlx_data->win_x / (double)mlx_data->win_y;
	mlx_data->win = mlx_new_window(mlx_data->mlx, mlx_data->win_x,
			mlx_data->win_y, "Ray.");
}
