/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:27:26 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/12 19:27:26 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "../../lib/miniRT.h"
# include "../intersect/intersect.h"

int			draw_scene(t_rt *rt);

t_intersect	get_closest_shape(t_xyz viewpoint, t_xyz ray, t_scene *scene);
t_intersect	ray_interects_sphere(t_xyz *viewpoint, t_xyz ray, t_sphere *sphere);
t_intersect	ray_intersects_plane(t_xyz *viewpoint, t_xyz ray, t_plane *plane);

void		draw_pixel(t_rt *rt, int x, int y, t_intersect intersect);
int			calculate_colour(t_intersect intersect, t_scene *scene);

t_intersect	check_shadows(t_scene *scene, t_xyz light_point,
				t_intersect intersect);
bool		intersects_sphere(t_xyz intersect_point, t_xyz light_xyz,
				t_list *spheres, t_xyz to_light);
bool		intersects_plane(t_xyz intersect_point, t_xyz light_xyz,
				t_list *planes, t_xyz to_light);

void		calculate_camera_right_up(t_camera *camera);

#endif
