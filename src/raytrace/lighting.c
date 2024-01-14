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

#define C1 1.8
#define C3 0.000005

static t_xyz	get_surface_normal(t_intersect intersect);
t_rgb			lit_colour(t_rgb base, t_light *light,
					double diffuse_intensity, t_rgb ambient_component);
t_rgb			get_ambient_colour(t_rgb base, t_ambience *ambient_lighting);

int	get_colour(t_intersect intersect, t_xyz point, t_scene *scene)
{
	double	diffuse_intensity;
	t_rgb	colour;
	t_xyz	light_direction;
	t_xyz	surface_normal;

	colour = get_ambient_colour(intersect.colour, scene->ambience);
	if (intersect.in_shadow)
		return (rgb_to_hex(colour));
	light_direction = v_normalize(v_subtract(*scene->light->point,
				point));
	surface_normal = get_surface_normal(intersect);
	diffuse_intensity = fmax(-1, fmin(1, v_dot(light_direction,
					surface_normal)));
	if (diffuse_intensity < 0)
		diffuse_intensity *= -1.0;
	if (intersect.light_distance > 0)
		diffuse_intensity /= (C1 + C3 * pow(intersect.light_distance, 2));
	colour = lit_colour(intersect.colour, scene->light,
			diffuse_intensity, colour);
	return (rgb_to_hex(colour));
}

t_rgb	lit_colour(t_rgb base, t_light *light,
				double diffuse_intensity, t_rgb ambient_component)
{
	t_rgb	light_colour;
	t_rgb	result;

	light_colour = rgb_scale(light->colour, light->brightness
			* diffuse_intensity * 1.5);
	light_colour = rgb_product(base, light_colour);
	result = rgb_add(light_colour, ambient_component);
	return (result);
}

t_rgb	get_ambient_colour(t_rgb base, t_ambience *ambient_lighting)
{
	t_rgb	ambient_component;
	t_rgb	result;

	ambient_component = rgb_product(base, ambient_lighting->colour);
	result = rgb_scale(ambient_component, ambient_lighting->lighting);
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
