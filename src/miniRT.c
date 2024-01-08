/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/08 20:00:52 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "math_utils.h"

void printRayInfo(float x, float y, float dx, float dy, t_vector *ray) {
    printf("Pixel (%.2f, %.2f):\n", x, y);
    printf("  dx: %.2f, dy: %.2f\n", dx, dy);
    printf("  Ray vector: (%.2f, %.2f, %.2f)\n", ray->x, ray->y, ray->z);
    printf("\n");
}


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

float raySphereIntersection(t_vector *ray_origin, t_vector *ray, t_sphere *sphere)
{
	// Calculate the vector from the ray origin to the sphere center
	t_vector *sphereToRay;
	
	sphereToRay = vector_sub(ray_origin, sphere->centre); 
	
	// Calculate coefficients of the quadratic equation for ray-sphere intersection
	float a = dot(ray, ray);
	float b = 2.0f * dot(sphereToRay, ray);
	float c = dot(sphereToRay, sphereToRay) - (ft_sqr(sphere->diameter / 2.0f));

	// Calculate the discriminant
	float discriminant = b * b - 4 * a * c;
	// If the discriminant is non-negative, there is an intersection
	free_vector(sphereToRay);
	return (discriminant >= 0);
}

void drawScene(t_vars *mlx, t_camera *camera, t_rt *rt)
{
	float x;
	float y;
	float dx;
	float dy;
	t_vector rayTarget;

	y = 0;
	/* viewport_setup(mlx, rt); */
	set_vector_to_single(&rayTarget, 0);
	while (y < mlx->win_y)
	{
		x = 0;
		while (x < mlx->win_x)
		{
			/* rayTarget = cpy_vector(vector_sub2(vector_add2(camera->pixel00_loc, vector_add2(vector_mul2(camera->pixel_delta_u, x), vector_mul2(camera->pixel_delta_v, y))),camera->center)); */
			// pixels to grid rangeing from -1 to 1;
			dx = (x / mlx->win_x) * 2.0f - 1.0f;
			dy = (y / mlx->win_y) * 2.0f - 1.0f;
			// Calculate the direction vector for the current ray
			set_vector_to(&rayTarget, dx, dy, camera->orientation->z);
			/* vector_normalize(&rayTarget); */
			if (raySphereIntersection(camera->view_point, &rayTarget, (t_sphere *)rt->scene->spheres->content) > 0)
			{
				printRayInfo(x,y,dx,dy,&rayTarget);
				mlx_pixel_put(mlx->mlx, mlx->win, (int)x, (int)y, 0xFFFFFF);
			}
			x++;
		}
		/* printf("converted x = %.2f to dx = %.2f \t converted y = %.2f to dy = %.2f\n", x, dx, y, dy); */
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
	drawScene(rt->mlx_data, (t_camera *)rt->scene->camera, rt);
	/* draw_sphere(rt->mlx_data, (t_sphere *)rt->scene->spheres->content); */
	// mlx_expose_hook(rt->mlx_data->win, draw, mlx_data);
	mlx_loop(rt->mlx_data->mlx);
	return (0);
}
