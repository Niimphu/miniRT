/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/08 19:10:15 by Kekuhne          ###   ########.fr       */
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
	float a = vector_lenght_sqr(ray);
	float b = 2 * dot(ray, sphereToRay);
	float c = vector_lenght_sqr(sphereToRay) - (ft_sqr(sphere->diameter) / 4.0f);

	// Calculate the discriminant
	float discriminant = b * b - 4 * a * c;
	// If the discriminant is non-negative, there is an intersection
	free_vector(sphereToRay);
	return (discriminant >= 0);
}

/* void	viewport_setup(t_vars *mlx, t_rt *rt)
{
	t_vector *focal_vector;

	rt->scene->camera->focal_lenght = 1.0f;
	set_vector_to(&focal_vector, 0, rt->scene->camera->focal_lenght);
	rt->scene->camera->viewport_height = 2.0f;
	rt->scene->camera->viewport_width = mlx->win_y / mlx->aspect_ratio;
	rt->scene->camera->center = new_vector();
	rt->scene->camera->center = set_vector_to_single(rt->scene->camera, 0);
	rt->scene->camera->viewport_u = new_vector();
	rt->scene->camera->viewport_u = set_vector_to(rt->scene->camera->viewport_u, rt->scene->camera->viewport_width,0,0);
	rt->scene->camera->viewport_v = new_vector();
	rt->scene->camera->viewport_v = set_vector_to(rt->scene->camera->viewport_v, 0,-rt->scene->camera->viewport_height,0);
	rt->scene->camera->pixel_delta_u = vector_div(rt->scene->camera->pixel_delta_u, rt->scene->camera->viewport_width);
	rt->scene->camera->pixel_delta_v = vector_div(rt->scene->camera->pixel_delta_v, rt->scene->camera->viewport_heigt);
	rt->scene->camera->viewport_upper_left = cpy_vector((vector_sub2(vector_sub2(rt->scene->camera->center, &focal_vector), vector_sub2(vector_div2(rt->scene->camera->viewport_u, 2.0f), vector_div2(rt->scene->camera->viewport_v, 2.0f)))));
	rt->scene->camera->pixel00_loc = cpy_vector(vector_add2(rt->scene->camera->viewport_upper_left, vector_mul2(vector_add2(rt->scene->camera->pixel_delta_u, rt->scene->camera->pixel_delta_v), 0.5f)));
}
 */
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
			dx = ((2.0f * x) / (float)mlx->win_x) - 1.0f;
			dy = ((2.0f * y) / (float)mlx->win_y) - 1.0f;
			// Calculate the direction vector for the current ray
			set_vector_to(&rayTarget,dx,
			dy ,
			camera->orientation->z);
			/* vector_normalize(&rayTarget); */
			printRayInfo(x,y,dx,dy,&rayTarget);
			if (raySphereIntersection(camera->view_point, &rayTarget, (t_sphere *)rt->scene->spheres->content) > 0)
				mlx_pixel_put(mlx->mlx, mlx->win, (int)x, (int)y, 0xFFFFFF);
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
