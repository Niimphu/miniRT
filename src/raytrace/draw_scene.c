/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:21:56 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/28 20:24:23 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS

# include "miniRT.h"
# include "draw.h"
# include "msaa.h"

static t_xyz	get_ray(t_vars *data, t_camera *camera, int x, int y);
static void		draw_closest_shape(t_vars *mlx, t_camera *camera, t_rt *rt);
static void		draw_closest_shape_msaa(t_vars *mlx, t_camera *camera,
					t_rt *rt);

int	draw_scene(t_rt *rt)
{
	calculate_camera_right_up(rt->scene->camera);
	if (rt->msaa)
		draw_closest_shape_msaa(rt->mlx_data, rt->scene->camera, rt);
	else
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
				draw_pixel(rt, (t_xyz){x, y, 0}, intersect, ray);
			x++;
		}
		y++;
	}
}

static void	draw_closest_shape_msaa(t_vars *mlx, t_camera *camera, t_rt *rt)
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
			print_pixel_msaa(rt, x, y, ray_info);
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

	scale = tanf(0.5 * (float)camera->fov * (M_PI / 180.0));
	dx = scale * data->aspect_ratio * (((x + 0.5) / data->win_x) * 2.0 - 1.0);
	dy = scale * (1.0 - ((y + 0.5) / data->win_y) * 2.0);
	result = v_add(v_add(v_scale(camera->right, dx),
				v_scale(camera->up, dy)), *camera->forward);
	result = v_normalize(result);
	return (result);
}

#endif
