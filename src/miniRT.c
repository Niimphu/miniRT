/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/04 17:30:26 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"

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
			float dx = x - sphere->centre->x;
			float dy = y - sphere->centre->x;
			float distance = sqrt(dx * dx + dy * dy);
			// If the pixel is within the radius of the sphere, draw it
			if (distance < sphere->diameter / 2)
				mlx_pixel_put(mlx->mlx, mlx->win, x, y, 0xFF0000);
			y++;
		}
		x++;
	}
}

int raySphereIntersection(t_vector *ray_origin, t_vector *ray, t_sphere *sphere)
{
	// Calculate the vector from the ray origin to the sphere center
	t_vector sphereToRay;
	set_vector_to(&sphereToRay, ray_origin->x - sphere->centre->x, ray_origin->y - sphere->centre->y, ray_origin->z - sphere->centre->z);

	// Calculate coefficients of the quadratic equation for ray-sphere intersection
	float a = ray->x * ray->x + ray->y * ray->y + ray->z * ray->z;
	float b = 2 * (ray->x * sphereToRay.x + ray->y * sphereToRay.y + ray->z * sphereToRay.z);
	float c = sphereToRay.x * sphereToRay.x + sphereToRay.y * sphereToRay.y + sphereToRay.z * sphereToRay.z - (sphere->diameter / 2) * (sphere->diameter / 2);

	// Calculate the discriminant
	float discriminant = b * b - 4 * a * c;

	// If the discriminant is non-negative, there is an intersection
	return discriminant >= 0;
}

t_vector	rotate_ray_x(t_vars *data, t_camera *camera, int x)
{
	t_vector	result;
	float		angle;

	angle = (x - (data->win_x - 1 / 2)) * (camera->fov_x / (data->win_x - 1));
	result.x = camera->view_point->x * cos(angle) + camera->view_point->z
		* sin(angle);
	result.z = -camera->view_point->x * sin(angle) + camera->view_point->z
		* cos(angle);
	result.x += camera->view_point->x;
	result.y = camera->view_point->y;
	result.z += camera->view_point->z;
	return (result);
}

t_vector	rotate_ray_y(t_vars *data, t_camera *camera, int y, t_vector *vec)
{
	t_vector	result;
	float		angle;

	angle = (y - (data->win_y - 1 / 2)) * (camera->fov_y / (data->win_y - 1));
	result.x = camera->view_point->x * cos(angle) + camera->view_point->z
		* sin(angle);
	result.z = -camera->view_point->x * sin(angle) + camera->view_point->z
		* cos(angle);
	result.x += camera->view_point->x;
	result.y = camera->view_point->y;
	result.z += camera->view_point->z;
	return (result);
}

void	draw_scene(t_vars *mlx, t_camera *camera, t_rt *rt)
{
	int			x;
	int			y;
	t_vector	ray;

	x = 0;
	set_vector_to_single(&ray, 0);
	while (x < mlx->win_x)
	{
		y = 0;
		while (y < mlx->win_y)
		{
			// Calculate the direction vector for the current ray
			set_vector_to(&ray, x - camera->view_point->x,
				y - camera->view_point->y,
				camera->fov_x - camera->view_point->z);
			// Normalize the ray vector
			vector_normalize(&ray);
			// Calculate the dot product between the camera orientation and the ray and
			// draw the pixel if it is within the field of view of the came
			if (raySphereIntersection(camera->view_point, &ray,
					(t_sphere *)rt->scene->spheres->content))
				mlx_pixel_put(mlx->mlx, mlx->win, x, y, 0xFFFFFF);
			y++;
		}
		x++;
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
            float distance = pointToPixel.x * plane.normal.x + pointToPixel.y * plane.normal.y + pointToPixel.z * plane.normal.z;

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
