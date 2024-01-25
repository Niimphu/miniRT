/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:21:56 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/20 08:40:12 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "xyz.h"
#include "shape.h"
#include "draw.h"

static void		calculate_camera_right_up(t_camera *camera);
static t_xyz	get_ray(t_vars *data, t_camera *camera, int x, int y);
static void		draw_closest_shape(t_vars *mlx, t_camera *camera, t_rt *rt);
/* static void		print_pixel(t_rt *rt, int x, int y, t_intersect intersect); */

int	draw_scene(t_rt *rt)
{
	calculate_camera_right_up(rt->scene->camera);
	draw_closest_shape(rt->mlx_data, rt->scene->camera, rt);
	return (0);
}

static void	calculate_camera_right_up(t_camera *camera)
{
	camera->right = v_normalize(v_cross(*camera->forward, (t_xyz){0, 1, 1}));
	camera->up = v_normalize(v_cross(camera->right, *camera->forward));
	camera->right = v_invert(camera->right);
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
			/* intersect = get_closest_shape(*camera->position, ray, rt->scene); */
			intersect = ray_intersects_cylinder(camera->position, ray, (t_cylinder *)rt->scene->cylinders->content);
			if (intersect.valid)
			{
				mlx_pixel_put(rt->mlx_data->mlx, rt->mlx_data->win, x, y,
					cylinder_colour((t_cylinder *) intersect.shape,
					intersect.point, rt->scene));
			}
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

/* static void	print_pixel(t_rt *rt, int x, int y, t_intersect intersect)
{
	if (intersect.type == SPHERE)
		mlx_pixel_put(rt->mlx_data->mlx, rt->mlx_data->win, x, y,
			sphere_colour((t_sphere *) intersect.shape,
				intersect.point, rt->scene));
	else if (intersect.type == PLANE)
		mlx_pixel_put(rt->mlx_data->mlx, rt->mlx_data->win, x, y,
			plane_colour((t_plane *) intersect.shape,
				intersect.point, rt->scene));
} */
