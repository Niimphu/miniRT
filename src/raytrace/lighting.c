/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:48:46 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/12 19:48:46 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "draw.h"
#include "printer.h"

static t_xyz	get_surface_normal(t_intersect intersect);
t_rgb			shadow_colour(t_rgb surface_colour, t_rgb ambient_colour);
t_rgb			lit_colour(t_rgb base, t_light *light,
					double diffuse_intensity, t_ambience *ambient_lighting);

int	get_colour(t_intersect intersect, t_xyz point, t_scene *scene)
{
	double	diffuse_intensity;
	t_rgb	colour;
	t_xyz	light_direction;
	t_xyz	surface_normal;

	if (intersect.in_shadow)
		return (rgb_to_hex(shadow_colour(intersect.colour,
					rgb_scale(scene->ambience->colour,
						scene->ambience->lighting))));
	light_direction = v_normalize(v_subtract(*scene->light->point,
				point));
	surface_normal = get_surface_normal(intersect);
	diffuse_intensity = fmax(-1, fmin(1, v_dot(light_direction,
					surface_normal)));
	if (diffuse_intensity < 0)
		diffuse_intensity *= -1.0;
	colour = lit_colour(intersect.colour, scene->light,
			diffuse_intensity, scene->ambience);
	return (rgb_to_hex(colour));
}

t_rgb	lit_colour(t_rgb base, t_light *light,
				double diffuse_intensity, t_ambience *ambient_lighting)
{
	t_rgb	result;
	t_rgb	light_colour;
	t_rgb	ambient_colour;
	t_rgb	total_light_colour;

	light_colour = rgb_scale(light->colour, light->brightness
			* diffuse_intensity * (1.0 - ambient_lighting->lighting));
	ambient_colour = rgb_scale(ambient_lighting->colour,
			ambient_lighting->lighting);
	total_light_colour = rgb_add(light_colour, ambient_colour);
	result.r = fmin(base.r, total_light_colour.r);
	result.g = fmin(base.g, total_light_colour.g);
	result.b = fmin(base.b, total_light_colour.b);
	return (result);
}

t_rgb	shadow_colour(t_rgb surface_colour, t_rgb ambient_colour)
{
	t_rgb	result;

	result.r = fmin(surface_colour.r, ambient_colour.r);
	result.g = fmin(surface_colour.g, ambient_colour.g);
	result.b = fmin(surface_colour.b, ambient_colour.b);
	return (result);
}

static t_xyz	get_surface_normal(t_intersect intersect)
{
	if (intersect.type == SPHERE)
		return (sphere_normal(intersect.shape, intersect.point));
	if (intersect.type == PLANE)
		return (plane_normal(intersect.shape));
	return ((t_xyz){0});
}
