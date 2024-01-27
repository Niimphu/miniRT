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
#include "../lighting/lighting.h"

void	draw_pixel(t_rt *rt, t_xyz coord, t_intersect intersect, t_xyz ray)
{
	int	colour;

	colour = rgb_to_hex(bounce(rt->scene, ray, 0, intersect));
	mlx_pixel_put(rt->mlx_data->mlx, rt->mlx_data->win, coord.x, coord.y,
		colour);
}

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
		{
			colour = add_direct_light(intersect.colour, colour, lighting);
			colour = combine_specular(intersect, lighting, colour,
					scene->camera);
		}
		light_list = light_list->next;
	}
	colour = combine_ambient(intersect.colour, colour, scene->ambience);
	return (rgb_to_hex(colour));
}
