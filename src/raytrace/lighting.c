/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:47:19 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/21 16:47:19 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"

#define C1 1.8
#define C3 0.000005

t_rgb	get_specular_component(t_lighting lighting, t_material material, t_intersect intersect, t_camera *camera)
{
	t_xyz	halfway;
	double	specular_factor;
	t_rgb	specular_component;

	halfway = get_halfway_vector(intersect.point, *lighting.light->point,
			*camera->position);
	specular_factor = pow(fmax(v_dot(lighting.surface_normal, halfway),
			0.0), material.shininess) * material.spec_coeff;
	specular_component = rgb_scale(lighting.light->colour,
			specular_factor * lighting.light->brightness * lighting.diffuse_intensity);
	return (specular_component);
}

t_rgb	combine_specular(t_intersect intersect, t_lighting lighting,
			t_rgb base, t_camera *camera)
{
	t_rgb	specular_component;
	t_rgb	result;

	specular_component = get_specular_component(lighting, intersect.material, intersect, camera);
	result = rgb_add(base, specular_component);
	return (result);
}

t_lighting	get_lighting(t_light *light, t_scene *scene,
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
	lighting.distance = p2p_distance(*light->point, intersection);
	if (lighting.distance > 0)
		lighting.diffuse_intensity /= (C1 + C3 * pow(lighting.distance, 2));
	lighting.light = light;
	return (lighting);
}

t_rgb	add_direct_light(t_rgb base, t_rgb colour, t_lighting lighting)
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

