/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:27:26 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/02 17:52:25 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "../../lib/miniRT.h"
# include "../intersect/intersect.h"

int			draw_scene(t_rt *rt);

t_intersect	get_closest_shape(t_xyz viewpoint, t_xyz ray, t_scene *scene);

void		draw_pixel(t_rt *rt, t_xyz coord, t_intersect intersect, t_xyz ray);
int			calculate_colour(t_intersect intersect, t_scene *scene);
t_rgb		bounce(t_scene *scene, t_xyz ray, int bounces,
				t_intersect intersect);

void		calculate_camera_right_up(t_camera *camera);

#endif
