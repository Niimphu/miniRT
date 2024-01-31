/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/12 17:45:42 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "draw.h"

int	raytrace(t_rt *rt)
{
	mlx_hook(rt->mlx_data->win, KeyPress, 1L << 0, key_pressed, rt);
	mlx_hook(rt->mlx_data->win, DestroyNotify, 0L, window_closed, rt);
	draw_scene(rt);
	mlx_expose_hook(rt->mlx_data->win, draw_scene, rt);
	mlx_loop(rt->mlx_data->mlx);
	return (0);
}

////print amount of time taken to render scene
//#include <sys/time.h>
//
//int	raytrace(t_rt *rt)
//{
//	struct timeval	start, end;
//	double			processing_time;
//
//	mlx_hook(rt->mlx_data->win, KeyPress, 1L << 0, key_pressed, rt);
//	mlx_hook(rt->mlx_data->win, DestroyNotify, 0L, window_closed, rt);
//	gettimeofday(&start, NULL);
//	draw_scene(rt);
//	gettimeofday(&end, NULL);
//	processing_time = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1e6;
//	printf("Draw time: %f seconds.\n", processing_time);
//	mlx_expose_hook(rt->mlx_data->win, draw_scene, rt);
//	mlx_loop(rt->mlx_data->mlx);
//	return (0);
//}
//