/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:20:03 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/12 19:20:03 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define A 0
#define B 1
#define C 2

#include "miniRT.h"
#include "xyz.h"
#include "shape.h"
#include "draw.h"

t_intersect	ray_interects_sphere(t_xyz *viewpoint, t_xyz ray, t_sphere *sphere)
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
