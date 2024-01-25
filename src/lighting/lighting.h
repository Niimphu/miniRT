/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:47:19 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/21 16:47:19 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHTING_H
# define LIGHTING_H

# include "draw.h"

typedef struct s_lighting
{
	t_light	*light;
	double	distance;
	double	diffuse_intensity;
	t_xyz	surface_normal;
}			t_lighting;

t_lighting	get_lighting(t_light *light, t_scene *scene,
				t_xyz intersection, t_intersect intersect);
t_rgb		add_direct_light(t_rgb base, t_rgb colour,
				t_lighting lighting);
t_rgb		combine_specular(t_intersect intersect, t_lighting lighting,
				t_rgb base, t_camera *camera);
t_rgb		combine_ambient(t_rgb base, t_rgb light_colour,
				t_ambience *ambient_lighting);

t_xyz		get_surface_normal(t_intersect intersect);
t_xyz		get_halfway_vector(t_xyz intersection, t_xyz light_pos,
				t_xyz camera_pos);

#endif
