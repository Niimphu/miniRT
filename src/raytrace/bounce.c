/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bounce.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:21:03 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/03 16:24:37 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "../lighting/lighting.h"

t_xyz	get_reflected_ray(t_xyz incident, t_xyz normal);

t_rgb	bounce(t_scene *scene, t_xyz ray, int bounces,
				t_intersect intersect)
{
	t_xyz		reflected;
	t_intersect	next_shape;
	t_rgb		next_colour;
	double		reflectivity;
	
	reflectivity = intersect.material.reflectivity;
	if (reflectivity == 0)
		return (hex_to_rgb(calculate_colour(intersect, scene)));
	reflected = get_reflected_ray(ray, get_surface_normal(intersect));
	next_shape = get_closest_shape(intersect.point, reflected, scene);
	if (!next_shape.valid || bounces > MAX_BOUNCES)
		return (hex_to_rgb(calculate_colour(intersect, scene)));
	next_colour = bounce(scene, reflected, ++bounces, next_shape);
	intersect.colour = hex_to_rgb(calculate_colour(intersect, scene));
	return (rgb_add(rgb_scale(intersect.colour, 1 - reflectivity),
			rgb_scale(next_colour, reflectivity)));
}

t_xyz	get_reflected_ray(t_xyz incident, t_xyz normal)
{
	t_xyz	reflected;

	incident = v_normalize(incident);
	normal = v_normalize(normal);
	reflected = v_subtract(incident,
			v_scale(normal, 2 * v_dot(incident, normal)));
	return (reflected);
}
