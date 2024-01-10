/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/10 14:00:05 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "maths/shape.h"

int	sphere_colour(t_sphere *sphere, t_intersect *data, t_scene *scene)
{
	double	diffuse_intensity;
	t_rgb	colour;
	t_xyz	light_direction;
	t_xyz	surface_normal;

	light_direction = v_normalize(v_subtract(*scene->light->point,
				data->point));
	surface_normal = s_surface_normal(sphere, data->point);
	diffuse_intensity = fmax(0, fmin(1, (light_direction.x * surface_normal.x
					+ light_direction.y * surface_normal.y
					+ light_direction.z * surface_normal.z)));
	colour = rgb_scale(sphere->colour, diffuse_intensity);
	return (rgb_to_hex(colour));
}

t_intersect	*ray_interects_sphere(t_xyz *viewpoint, t_xyz ray,
		t_sphere *sphere)
{
	t_xyz	to_sphere;
	double	projection;
	t_xyz	closest_point;
	double	distance_squared;

	to_sphere = v_subtract(*sphere->centre, *viewpoint);
	projection = v_dot(to_sphere, ray);
	if (projection < 0)
		return (NULL);
	closest_point.x = viewpoint->x + projection * ray.x;
	closest_point.y = viewpoint->y + projection * ray.y;
	closest_point.z = viewpoint->z + projection * ray.z;
	distance_squared = pow(closest_point.x - sphere->centre->x, 2)
		+ pow(closest_point.y - sphere->centre->y, 2)
		+ pow(closest_point.z - sphere->centre->z, 2);
	t_xyz	intersection_point;
	t_xyz	to_intersection = v_subtract(closest_point, *sphere->centre);
	double	length = p2p_distance(*viewpoint, to_intersection);
	if (length < 0)
		return (NULL);
	intersection_point.x = sphere->centre->x + (to_intersection.x / length)
		* (sphere->diameter / 2);
	intersection_point.y = sphere->centre->y + (to_intersection.y / length)
		* (sphere->diameter / 2);
	intersection_point.z = sphere->centre->z + (to_intersection.z / length)
		* (sphere->diameter / 2);
	if (distance_squared <= pow(sphere->diameter / 2, 2))
		return (new_intersect(intersection_point, length,
				(void *)sphere, SPHERE));
	else
		return (NULL);
}

t_xyz	get_ray(t_vars *data, t_camera *camera, int x, int y)
{
	double	dx;
	double	dy;
	double	scale;
	t_xyz	result;

	scale = tanf(0.5f * (float)camera->fov * (M_PI / 180.0));
	dx = scale * data->aspect_ratio * (((double)x / data->win_x) * 2.0 - 1.0);
	dy = scale * (1.0 - ((double)y / data->win_y) * 2.0);
	result = v_add(v_add(v_scale(camera->right, dx),
				v_scale(camera->up, dy)), v_scale(*camera->forward, scale));
	return (v_normalize(result));
}

void	calculate_camera_right_up(t_camera *camera)
{
	camera->right = v_normalize(v_cross(*camera->forward, (t_xyz){0, 1, 1}));
	camera->up = v_normalize(v_cross(camera->right, *camera->forward));
	camera->right = v_invert(camera->right);
}

int	draw_scene(t_vars *mlx, t_camera *camera, t_rt *rt)
{
	int			x;
	int			y;
	t_xyz		ray;
	t_intersect	*intersect;

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
			intersect = ray_interects_sphere(camera->position, ray,
					(t_sphere *)rt->scene->spheres->content);
			if (intersect)
				mlx_pixel_put(mlx->mlx, mlx->win, x, y,
					sphere_colour((t_sphere *)intersect->shape,
						intersect, rt->scene));
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
            t_xyz pixel = {x, y, 0};

            // Calculate the distance from the point to the plane
            t_xyz pointToPixel = {pixel->x - plane.point.x, pixel.y - plane.point.y, pixel.z - plane.point.z};
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
