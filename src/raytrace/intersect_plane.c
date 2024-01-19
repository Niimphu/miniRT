/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:20:58 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/19 20:20:58 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "xyz.h"
#include "draw.h"

t_intersect	ray_intersects_plane(t_xyz *viewpoint, t_xyz ray, t_plane *plane)
{
	t_intersect	intersection;
	double		dot_product;
	double		t;

	intersection = new_intersect();
	dot_product = v_dot(*plane->norm, ray);
	if (dot_product == 0)
		return (intersection);
	t = v_dot(v_subtract(*plane->point, *viewpoint), *plane->norm)
		/ dot_product;
	if (t < 0.0)
		return (intersection);
	intersection.distance = t;
	intersection.point = v_add(*viewpoint, v_scale(ray, t));
	intersection.shape = plane;
	intersection.colour = plane->colour;
	intersection.type = PLANE;
	intersection.valid = true;
	return (intersection);
}
