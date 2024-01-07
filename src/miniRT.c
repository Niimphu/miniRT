/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/05 15:27:04 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"
#include "printer.h"

void draw_sphere(t_vars *mlx, t_sphere *sphere)
{
	int	x;
	int	y;

	x = 0;
	printf("x %.2f\n", sphere->centre->x);
	printf("y %.2f\n", sphere->centre->y);
	printf("d %.2f\n", sphere->diameter);
	// Iterate through pixels in the window
	while(x < mlx->win_x)
	{
		y = 0;
		while (y < mlx->win_y)
		{
			// Calculate distance from the center of the sphere
			double dx = x - sphere->centre->x;
			double dy = y - sphere->centre->x;
			double distance = sqrt(dx * dx + dy * dy);
			// If the pixel is within the radius of the sphere, draw it
			if (distance < sphere->diameter / 2)
				mlx_pixel_put(mlx->mlx, mlx->win, x, y, 0xFF0000);
			y++;
		}
		x++;
	}
}

double	ray_interects_sphere(t_vector *viewpoint, t_vector ray, t_sphere *sphere)
{
	t_vector	to_sphere;

	to_sphere = v_diff(*sphere->centre, *viewpoint);


	double	projection;

	projection = dot(to_sphere, ray);


	if (projection < 0) //Intersection is behind viewpoint
		return (0);


	t_vector	closest_point;

	closest_point.x = viewpoint->x + projection * ray.x;
	closest_point.y = viewpoint->y + projection * ray.y;
	closest_point.z = viewpoint->z + projection * ray.z;


	double distance_to_sphere = sqrt(pow(closest_point.x - sphere->centre->x, 2)
			+ pow(closest_point.y - sphere->centre->y, 2)
			+ pow(closest_point.z - sphere->centre->z, 2));


	if (distance_to_sphere <= sphere->diameter / 2) //makes sure we are not inside the sphere
		return (distance_to_sphere);
	else
		return (0);
}

t_vector	get_ray(t_vars *data, t_camera *camera, int x, int y)
{
	t_vector	result;
	t_vector	right;
	t_vector	up;
	double		normalised_x;
	double		normalised_y;

	right = vector_normalize(cross(*camera->orientation, (t_vector){0, 1, 0}));
	up = vector_normalize(cross(right, *camera->orientation));

	up.y *= -1.0;

	normalised_x = (2.0 * ((double)x + 0.5) / (double)data->win_x - 1.0)
		* ((double)data->win_x / (double)data->win_y)
		* tan(camera->fov_x * M_PI / 360.0);
	normalised_y = (2.0 * ((double)y + 0.5) / (double)data->win_y)
		* tan(camera->fov_y * M_PI / 360.0);

	result.x = camera->view_point->x + normalised_x * right.x
		+ normalised_y * up.x;
	result.y = camera->view_point->y + normalised_x * right.y
		+ normalised_y * up.y;
	result.z = camera->view_point->z + normalised_x * right.z
		- normalised_y * up.z;
	return (result);
}

void	draw_scene(t_vars *mlx, t_camera *camera, t_rt *rt)
{
	int			x;
	int			y;
	t_vector	ray;

	y = 0;
	printf("fov: %i, %f\n", camera->fov_x, camera->fov_y);
	while (y < mlx->win_y)
	{
		x = 0;
		while (x < mlx->win_x)
		{
			// Calculate the direction vector for the current ray
			ray = get_ray(mlx, camera, x, y);

			t_vector point_along_ray;
			point_along_ray.x = camera->view_point->x + 1000.0 * ray.x;
			point_along_ray.y = camera->view_point->y + 1000.0 * ray.y;
			point_along_ray.z = camera->view_point->z + 1000.0 * ray.z;

			print_vector_info(&point_along_ray);



			// Calculate the dot product between the camera orientation and the ray and
			// draw the pixel if it is within the field of view of the came
			if (ray_interects_sphere(camera->view_point, ray,
					(t_sphere *)rt->scene->spheres->content))
				mlx_pixel_put(mlx->mlx, mlx->win, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
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
	// mlx_expose_hook(rt->mlx_data->win, draw, mlx_data);
	mlx_loop(rt->mlx_data->mlx);
	return (0);
}
