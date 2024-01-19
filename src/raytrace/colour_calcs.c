/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour_calcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 17:30:00 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/19 17:30:00 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "draw.h"

#define C1 1.8
#define C3 0.000005

static t_lighting		get_lighting(t_light *light, t_scene *scene,
							t_xyz intersection, t_intersect intersect);
static t_rgb			add_light(t_rgb base, t_rgb colour,
							t_lighting lighting);
t_rgb					combine_ambient(t_rgb base, t_rgb light_colour,
							t_ambience *ambient_lighting);

int	calculate_colour(t_intersect intersect, t_scene *scene)
{
	t_rgb		colour;
	t_list		*light_list;
	t_light		*light;
	t_lighting	lighting;

	light_list = scene->lights;
	colour = (t_rgb){0};
	while (light_list)
	{
		light = light_list->content;
		lighting = get_lighting(light, scene, intersect.point, intersect);
		if (lighting.light)
			colour = add_light(intersect.colour, colour, lighting);
		light_list = light_list->next;
	}
	colour = combine_ambient(intersect.colour, colour, scene->ambience);
	return (rgb_to_hex(colour));
}

static t_lighting	get_lighting(t_light *light, t_scene *scene,
						t_xyz intersection, t_intersect intersect)
{
	t_lighting	lighting;
	t_xyz		light_direction;

	lighting.light = NULL;
	light_direction = v_normalize(v_subtract(*light->point, intersection));
	if (intersects_sphere(intersection, *light->point,
			scene->spheres, light_direction) || intersects_plane(intersection,
			*light->point, scene->planes, light_direction))
		return (lighting);
	lighting.surface_normal = get_surface_normal(intersect);
	lighting.diffuse_intensity = fmax(-1, fmin(1, v_dot(light_direction,
					lighting.surface_normal)));
	if (lighting.diffuse_intensity < 0)
		lighting.diffuse_intensity *= -1.0;
	if (lighting.distance > 0)
		lighting.diffuse_intensity /= (C1 + C3 * pow(lighting.distance, 2));
	lighting.light = light;
	return (lighting);
}

static t_rgb	add_light(t_rgb base, t_rgb colour, t_lighting lighting)
{
	t_rgb	light_colour;
	t_light	*light;

	light = lighting.light;
	light_colour = rgb_scale(light->colour, light->brightness
			* lighting.diffuse_intensity);
	light_colour = rgb_product(base, light_colour);
	colour = rgb_add(light_colour, colour);
	return (colour);
}

t_rgb	get_ambient_colour(t_rgb base, t_ambience *ambient_lighting)
{
	t_rgb	ambient_component;
	t_rgb	result;

	ambient_component = rgb_product(base, ambient_lighting->colour);
	result = rgb_scale(ambient_component, ambient_lighting->lighting);
	return (result);
}

t_rgb	combine_ambient(t_rgb base, t_rgb light_colour,
											t_ambience *ambient_lighting)
{
	t_rgb	ambient_component;
	t_rgb	result;

	ambient_component = rgb_scale(rgb_product(base,
				ambient_lighting->colour), ambient_lighting->lighting);
	result = rgb_add(light_colour, ambient_component);
	return (result);
}
