/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:20:06 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/12 19:20:06 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "xyz.h"
#include "shape.h"
#include "draw.h"

t_intersect	ray_intersects_plane(t_xyz *viewpoint, t_xyz ray, t_plane *plane)
{
	t_intersect	intersection;
	double		dot_product;
	double		t;

	intersection = new_intersect();
	dot_product = v_dot(*plane->norm, ray);
	if (dot_product == 0)
		return (intersection);
	t = ((plane->point->x - viewpoint->x) * plane->norm->x
			+ (plane->point->y - viewpoint->y) * plane->norm->y
			+ (plane->point->z - viewpoint->z) * plane->norm->z) / dot_product;
	if (t < 0.0)
		return (intersection);
	intersection.distance = t;
	intersection.point = v_add(*viewpoint, v_scale(ray, t));
	intersection.shape = plane;
	intersection.colour = plane->colour;
	intersection.type = PLANE;
	intersection.valid = true;
	return (intersection);
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
