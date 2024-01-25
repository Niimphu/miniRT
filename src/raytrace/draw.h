/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:27:26 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/14 19:50:24 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "../../lib/miniRT.h"

int			draw_scene(t_rt *rt);

t_intersect	get_closest_shape(t_xyz viewpoint, t_xyz ray, t_scene *scene);
t_intersect	ray_interects_sphere(t_xyz *viewpoint, t_xyz ray, t_sphere *sphere);
t_intersect	ray_intersects_plane(t_xyz *viewpoint, t_xyz ray, t_plane *plane);
t_intersect	ray_intersects_cylinder(t_xyz *viewpoint, t_xyz ray, t_cylinder *cl);

int			sphere_colour(t_sphere *sphere, t_xyz point, t_scene *scene);
int			plane_colour(t_plane *plane, t_xyz point, t_scene *scene);
int			cylinder_colour(t_cylinder *cl, t_xyz point, t_scene *scene);

#endif
