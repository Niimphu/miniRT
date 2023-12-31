/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/03 13:17:18 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/miniRT.h"

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
	mlx_data->win_x = 1280;
	mlx_data->win_y = 720;

	mlx_data->win = mlx_new_window(mlx_data->mlx, mlx_data->win_x, mlx_data->win_y, "Ray.");
}
