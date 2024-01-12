/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/12 17:45:42 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define A 0
#define B 1
#define C 2

#include "miniRT.h"
#include "xyz.h"
#include "printer.h"
#include "maths/shape.h"

int	sphere_colour(t_sphere *sphere, t_xyz point, t_scene *scene)
{
	double	diffuse_intensity;
	t_rgb	colour;
	t_xyz	light_direction;
	t_xyz	surface_normal;

	light_direction = v_normalize(v_subtract(*scene->light->point,
				point));
	surface_normal = s_surface_normal(sphere, point);
	diffuse_intensity = fmax(0, fmin(1, (light_direction.x * surface_normal.x
					+ light_direction.y * surface_normal.y
					+ light_direction.z * surface_normal.z)));
	colour = rgb_scale(sphere->colour, diffuse_intensity);
	colour = rgb_add(colour, rgb_scale(scene->ambience->colour,
				scene->ambience->lighting));
	return (rgb_to_hex(colour));
}

int	plane_colour(t_plane *plane, t_xyz point, t_scene *scene)
{
	double	diffuse_intensity;
	t_rgb	colour;
	t_xyz	light_direction;
	t_xyz	surface_normal;

	surface_normal = *plane->norm;
	light_direction = v_normalize(v_subtract(*scene->light->point,
				point));
	diffuse_intensity = fmax(0, fmin(1, (light_direction.x * surface_normal.x
					+ light_direction.y * surface_normal.y
					+ light_direction.z * surface_normal.z)));
	colour = rgb_scale(plane->colour, diffuse_intensity);
	colour = rgb_add(colour, rgb_scale(scene->ambience->colour,
				scene->ambience->lighting));
	return (rgb_to_hex(colour));
}

t_intersect	ray_interects_sphere(t_xyz *viewpoint, t_xyz ray,
		t_sphere *sphere)
{
	t_xyz		to_sphere_centre;
	double		discr_vars[3];
	double		discriminant;
	t_intersect	intersection;

	to_sphere_centre = v_subtract(*viewpoint, *sphere->centre);
	discr_vars[A] = v_dot(ray, ray);
	discr_vars[B] = 2.0 * v_dot(to_sphere_centre, ray);
	discr_vars[C] = v_dot(to_sphere_centre, to_sphere_centre)
		- (pow(sphere->diameter, 2) * 0.25);
	discriminant = pow(discr_vars[B], 2) - 4 * discr_vars[A] * discr_vars[C];
	intersection = new_intersect();
	if (discriminant < 0)
		return (new_intersect());
	intersection.distance = (-(discr_vars[B]) - sqrt(discriminant))
		/ (2.0 * discr_vars[A]);
	if (intersection.distance < 0)
		return (intersection);
	intersection.point = v_add(*viewpoint, v_scale(ray,
				intersection.distance));
	intersection.shape = sphere;
	intersection.type = SPHERE;
	intersection.colour = sphere->colour;
	intersection.valid = true;
	return (intersection);
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

t_intersect	get_closest_sphere(t_xyz viewpoint, t_xyz ray, t_list *spheres)
{
	t_sphere	*sphere;
	t_intersect	closest;
	t_intersect	new;

	while (spheres)
	{
		sphere = (t_sphere *)spheres->content;
		new = ray_interects_sphere(&viewpoint, ray, sphere);
		if (!closest.valid || (new.valid && (new.distance < closest.distance)))
			closest = new;
		spheres = spheres->next;
	}
	return (closest);
}

t_intersect	get_closest_plane(t_xyz viewpoint, t_xyz ray, t_list *planes)
{
	t_plane		*plane;
	t_intersect	closest;
	t_intersect	new;

	while (planes)
	{
		plane = (t_plane *)planes->content;
		new = ray_intersect_plane(&viewpoint, ray, plane);
		if (!closest.valid || (new.valid && (new.distance < closest.distance)))
			closest = new;
		planes = planes->next;
	}
	return (closest);
}

t_intersect	get_closest_shape(t_xyz viewpoint, t_xyz ray, t_scene *scene)
{
	t_intersect	closest_sphere;
	t_intersect	closest_plane;
	t_intersect	closest_cylinder;

	closest_sphere = get_closest_sphere(viewpoint, ray, scene->spheres);
	closest_plane = get_closest_plane(viewpoint, ray, scene->planes);
	if (closest_plane.distance < closest_sphere.distance)
		return (closest_plane);
	(void)closest_sphere;
	(void)closest_cylinder;
	return (closest_plane);
}

void	print_pixel(t_rt *rt, int x, int y, t_intersect intersect)
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

void	find_intersections(t_vars *mlx, t_camera *camera, t_rt *rt)
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
//			intersect = get_closest_shape(*camera->position, ray, rt->scene);
			intersect = ray_intersect_plane(camera->position, ray,
					(t_plane *)(rt->scene->planes->next->content));
			if (intersect.valid)
				print_pixel(rt, x, y, intersect);
			x++;
		}
		y++;
	}
}

int	draw_scene(t_rt *rt)
{
	calculate_camera_right_up(rt->scene->camera);
	find_intersections(rt->mlx_data, rt->scene->camera, rt);
	return (0);
}

int	raytrace(t_rt *rt)
{
	mlx_hook(rt->mlx_data->win, KeyPress, 1L << 0, key_pressed, rt);
	mlx_hook(rt->mlx_data->win, DestroyNotify, 0L, window_closed, rt);
	draw_scene(rt);
	mlx_expose_hook(rt->mlx_data->win, draw_scene, rt);
	mlx_loop(rt->mlx_data->mlx);
	return (0);
}
