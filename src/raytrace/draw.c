/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:21:56 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/12 19:21:56 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "xyz.h"
#include "shape.h"
#include "draw.h"

static t_xyz	get_ray(t_vars *data, t_camera *camera, int x, int y);
static void		draw_closest_shape(t_vars *mlx, t_camera *camera, t_rt *rt);
static void		print_pixel(t_rt *rt, int x, int y, t_intersect intersect);

int	draw_scene(t_rt *rt)
{
	calculate_camera_right_up(rt->scene->camera);
	draw_closest_shape(rt->mlx_data, rt->scene->camera, rt);
	return (0);
}

static void	draw_closest_shape(t_vars *mlx, t_camera *camera, t_rt *rt)
{
	int			x;
	int			y;
	t_xyz		ray;
	t_intersect	intersect;

	y = 0;
	while (y < mlx->win_y)
	{
		x = 0;
		while (x < mlx->win_x)
		{
			ray = get_ray(mlx, camera, x, y);
			intersect = get_closest_shape(*camera->position, ray, rt->scene);
			if (intersect.valid)
				print_pixel(rt, x, y, intersect);
			x++;
		}
		y++;
	}
}

static t_xyz	get_ray(t_vars *data, t_camera *camera, int x, int y)
{
	double	dx;
	double	dy;
	double	scale;
	t_xyz	result;

	scale = tanf(0.5f * (float)camera->fov * (M_PI / 180.0));
	dx = scale * data->aspect_ratio * (((double)x / data->win_x) * 2.0 - 1.0);
	dy = scale * (1.0 - ((double)y / data->win_y) * 2.0);
	result = v_add(v_add(v_scale(camera->right, dx),
				v_scale(camera->up, dy)),
			v_scale(*camera->forward, scale));
	return (v_normalize(result));
}

static void	print_pixel(t_rt *rt, int x, int y, t_intersect intersect)
{
	if (intersect.type == SPHERE)
		mlx_pixel_put(rt->mlx_data->mlx, rt->mlx_data->win, x, y,
			sphere_colour((t_sphere *) intersect.shape,
				intersect.point, rt->scene));
	else if (intersect.type == PLANE)
		mlx_pixel_put(rt->mlx_data->mlx, rt->mlx_data->win, x, y,
			plane_colour((t_plane *) intersect.shape,
				intersect.point, rt->scene));
}
