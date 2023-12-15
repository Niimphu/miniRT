/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/12 18:03:25 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/miniRT.h"

void	create_window(t_vars *mlx_data);

void	initialise(t_vars *mlx_data)
{
	mlx_data->mlx = mlx_init();
	create_window(mlx_data);
}

void	create_window(t_vars *mlx_data)
{
	const int	x = 1280;
	const int	y = 720;

	mlx_data->win = mlx_new_window(mlx_data->mlx, x, y, "Ray.");
}
