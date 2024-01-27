/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msaa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:54:44 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/15 18:25:07 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "msaa.h"
#include "xyz.h"
#include "draw.h"

static t_msaa	get_ray_info(t_rt *rt, t_camera *camera, int x, int y);
static t_xyz	get_ray(t_vars *data, t_camera *camera, double x, double y);
static t_msaa	process_shadows(t_scene *scene, t_msaa ray_info);
static void		print_pixel(t_rt *rt, int x, int y, t_msaa ray_info);

void	draw_closest_shape_msaa(t_vars *mlx, t_camera *camera, t_rt *rt)
{
	int			x;
	int			y;
	t_msaa		ray_info;

	y = 0;
	while (y < mlx->win_y)
	{
		x = 0;
		while (x < mlx->win_x)
		{
			ray_info = get_ray_info(rt, camera, x, y);
			ray_info = process_shadows(rt->scene, ray_info);
			print_pixel(rt, x, y, ray_info);
			x++;
		}
		y++;
	}
}

static t_msaa	get_ray_info(t_rt *rt, t_camera *camera, int x, int y)
{
	t_msaa	result;

	result.rays[0] = get_ray(rt->mlx_data, camera, x + 0.3, y + 0.2);
	result.rays[1] = get_ray(rt->mlx_data, camera, x + 0.8, y + 0.3);
	result.rays[2] = get_ray(rt->mlx_data, camera, x + 0.2, y + 0.7);
	result.rays[3] = get_ray(rt->mlx_data, camera, x + 0.7, y + 0.8);
	result.intersects[0] = get_closest_shape(*camera->position,
			result.rays[0], rt->scene);
	result.intersects[1] = get_closest_shape(*camera->position,
			result.rays[1], rt->scene);
	result.intersects[2] = get_closest_shape(*camera->position,
			result.rays[2], rt->scene);
	result.intersects[3] = get_closest_shape(*camera->position,
			result.rays[3], rt->scene);
	return (result);
}

static t_msaa	process_shadows(t_scene *scene, t_msaa ray_info)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (ray_info.intersects[i].valid)
			ray_info.colours[i] = rgb_to_hex(bounce(scene, ray_info.rays[i], 0,
						ray_info.intersects[i]));
		else
			ray_info.colours[i] = 0x000000;
		i++;
	}
	return (ray_info);
}

static t_xyz	get_ray(t_vars *data, t_camera *camera, double x, double y)
{
	double	dx;
	double	dy;
	double	scale;
	t_xyz	result;

	scale = tanf(0.5 * (float)camera->fov * (M_PI / 180.0));
	dx = scale * data->aspect_ratio * ((x / data->win_x) * 2.0 - 1.0);
	dy = scale * (1.0 - (y / data->win_y) * 2.0);
	result = v_add(v_add(v_scale(camera->right, dx),
				v_scale(camera->up, dy)), *camera->forward);
	result = v_normalize(result);
	return (result);
}

static void	print_pixel(t_rt *rt, int x, int y, t_msaa ray_info)
{
	t_rgb	colour;

	colour = average_4colour(hex_to_rgb(ray_info.colours[0]),
			hex_to_rgb(ray_info.colours[1]), hex_to_rgb(ray_info.colours[2]),
			hex_to_rgb(ray_info.colours[3]));
	mlx_pixel_put(rt->mlx_data->mlx, rt->mlx_data->win, x, y,
		rgb_to_hex(colour));
}
