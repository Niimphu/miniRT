/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/09 16:56:01 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
#include "printer.h"
#include "colour.h"



double	ray_interects_sphere(t_vector *viewpoint, t_vector ray, t_sphere *sphere)
{
	t_vector	to_sphere;

	to_sphere = v_diff(*sphere->centre, *viewpoint);


	double	projection;

	projection = v_dot(to_sphere, ray);
	if (projection < 0)
		return (0);


	t_vector	closest_point;

	closest_point.x = viewpoint->x + projection * ray.x;
	closest_point.y = viewpoint->y + projection * ray.y;
	closest_point.z = viewpoint->z + projection * ray.z;


	double	distance_squared;
	distance_squared = pow(closest_point.x - sphere->centre->x, 2)
		+ pow(closest_point.y - sphere->centre->y, 2)
		+ pow(closest_point.z - sphere->centre->z, 2);


	if (distance_squared <= pow(sphere->diameter / 2, 2))
		return (distance_squared);
	else
		return (0);
}

t_vector	get_ray(t_vars *data, t_camera *camera, int x, int y)
{
	double		dx;
	double		dy;
	double		scale;
	t_vector	result;

	scale = tanf(0.5f * (float)camera->fov * (M_PI / 180.0));
	dx = scale * data->aspect_ratio * (((double)x / data->win_x) * 2.0 - 1.0);
	dy = scale * (1.0 - ((double)y / data->win_y) * 2.0);
//	result = (t_vector){dx, dy, camera->forward->z};
//	result = v_add(result, v_scale(camera->right, dx));
//	result = v_add(result, v_scale(camera->up, dy));
//	return (v_normalize(result));

	result = v_add(v_add(v_scale(camera->right, dx),
				v_scale(camera->up, dy)), v_scale(*camera->forward, scale));

	return (v_normalize(result));
}

//{
//	t_vector	result;
//	t_vector	right;
//	t_vector	up;
//	t_vector	forward;
//	double		normalised_x;
//	double		normalised_y;
//
//	forward = v_normalize(*camera->forward);
//	up = v_normalize(v_cross(forward, (t_vector){0, 1, 0}));
//	right = v_normalize(v_cross(up, forward));
//
//	normalised_x = (2.0 * ((double)x + 0.5) / (double)data->win_x - 1.0)
//		* ((double)data->win_x / (double)data->win_y)
//		* tan(camera->fov * M_PI / 180.0);
//	normalised_y = (1.0 - 2.0 * ((double)y + 0.5) / (double)data->win_y)
//		* tan(camera->fov_y * M_PI / 180.0);
//
//	result.x = camera->position->x + normalised_x * right.x
//		+ normalised_y * up.x + forward.x;
//	result.y = camera->position->y + normalised_x * right.y
//		+ normalised_y * up.y + forward.y;
//	result.z = camera->position->z + normalised_x * right.z
//		- normalised_y * up.z + forward.z;
//	return (result);
//
//}

void	calculate_camera_right_up(t_camera *camera)
{
	camera->right = v_normalize(v_cross(*camera->forward, (t_vector){0, 1, 1}));
	camera->up = v_normalize(v_cross(camera->right, *camera->forward));
	camera->right = v_invert(camera->right);
}

int	draw_scene(t_vars *mlx, t_camera *camera, t_rt *rt)
{
	int			x;
	int			y;
	t_vector	ray;

	calculate_camera_right_up(camera);
	y = 0;
	while (y < mlx->win_y)
	{
		x = 0;
		while (x < mlx->win_x)
		{
			// Calculate the direction vector for the current ray
			ray = get_ray(mlx, camera, x, y);

			// Calculate the v_dot product between the camera forward and the ray and
			// draw the pixel if it is within the field of view of the came
			if (ray_interects_sphere(camera->position, ray,
					(t_sphere *)rt->scene->spheres->content))
				mlx_pixel_put(mlx->mlx, mlx->win, x, y,
					rgb_to_hex(((t_sphere *)rt->scene->spheres->content)->colour));
			x++;
		}
		y++;
	}
	printf("\nDONE\n\n");
	return (0);
}

/* void drawPlane(void *mlx, void *win, t_plane plane, int width, int height) {
	int x, y;

	for (x = 0; x < width; x++) {
		for (y = 0; y < height; y++) {
            // Calculate the position vector for the pixel
            t_vector pixel = {x, y, 0};

            // Calculate the distance from the point to the plane
            t_vector pointToPixel = {pixel->x - plane.point.x, pixel.y - plane.point.y, pixel.z - plane.point.z};
            double distance = pointToPixel.x * plane.normal.x + pointToPixel.y * plane.normal.y + pointToPixel.z * plane.normal.z;

            // Draw the pixel if it is close to the plane
            if (fabs(distance) < 2.0) {
                mlx_pixel_put(mlx, win, x, y, 0xFFFFFF); // 0xFFFFFF is white color
            }
        }
    }
} */

int	raytrace(t_rt *rt)
{
	mlx_hook(rt->mlx_data->win, KeyPress, 1L << 0, key_pressed, rt);
	mlx_hook(rt->mlx_data->win, DestroyNotify, 0L, window_closed, rt);
	draw_scene(rt->mlx_data, (t_camera *)rt->scene->camera, rt);
	/* draw_sphere(rt->mlx_data, (t_sphere *)rt->scene->spheres->content); */
//	mlx_expose_hook(rt->mlx_data->win, draw_scene, rt->mlx_data);
	mlx_loop(rt->mlx_data->mlx);
	return (0);
}
