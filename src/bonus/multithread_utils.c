/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithread_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:59:24 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/30 18:59:24 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"
#include "../raytrace/msaa.h"
#include "../raytrace/draw.h"

#ifdef BONUS

t_thread_info	*create_threaddata(t_rt *rt, int start, int end)
{
	t_thread_info	*data;

	data = ft_calloc(1, sizeof(t_thread_info));
	if (!data)
		return (NULL);
	data->mlx = rt->mlx_data;
	data->camera = rt->scene->camera;
	data->rt = rt;
	data->start_y = start;
	data->end_y = end;
	return (data);
}

int	start(int i, t_rt *rt)
{
	return (i * rt->mlx_data->win_y / THREADS);
}

int	end(int i, t_rt *rt)
{
	return ((i + 1) * rt->mlx_data->win_y / THREADS);
}

void	draw_pixel(t_rt *rt, t_xyz coord, t_intersect intersect, t_xyz ray)
{
	int	colour;

	colour = rgb_to_hex(bounce(rt->scene, ray, 0, intersect));
	pthread_mutex_lock(&rt->print_lock);
	mlx_pixel_put(rt->mlx_data->mlx, rt->mlx_data->win, coord.x, coord.y,
		colour);
	pthread_mutex_unlock(&rt->print_lock);
}

void	print_pixel_msaa(t_rt *rt, int x, int y, t_msaa ray_info)
{
	t_rgb	colour;

	colour = average_4colour(hex_to_rgb(ray_info.colours[0]),
			hex_to_rgb(ray_info.colours[1]), hex_to_rgb(ray_info.colours[2]),
			hex_to_rgb(ray_info.colours[3]));
	pthread_mutex_lock(&rt->print_lock);
	mlx_pixel_put(rt->mlx_data->mlx, rt->mlx_data->win, x, y,
		rgb_to_hex(colour));
	pthread_mutex_unlock(&rt->print_lock);
}

#endif
