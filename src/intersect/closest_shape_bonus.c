/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_shape_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:50:42 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/13 16:50:42 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/miniRT.h"
#include "../raytrace/draw.h"

t_intersect	get_closest_cone(t_xyz viewpoint, t_xyz ray, t_list *cones)
{
	t_cone		*cone;
	t_intersect	closest;
	t_intersect	new;

	closest = new_intersect();
	while (cones)
	{
		cone = (t_cone *)cones->content;
		new = ray_intersects_cone(&viewpoint, ray, cone);
		if (!closest.valid || (new.valid && (new.distance < closest.distance)))
			closest = new;
		cones = cones->next;
	}
	return (closest);
}

t_intersect	get_closest_triangle(t_xyz viewpoint, t_xyz ray, t_list *triangles)
{
	t_triangle	*triangle;
	t_intersect	closest;
	t_intersect	new;

	closest = new_intersect();
	while (triangles)
	{
		triangle = (t_triangle *) triangles->content;
		new = ray_intersects_triangle(&viewpoint, ray, triangle);
		if (!closest.valid || (new.valid && (new.distance < closest.distance)))
			closest = new;
		triangles = triangles->next;
	}
	return (closest);
}
