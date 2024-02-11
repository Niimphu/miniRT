/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_triangle.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 17:41:05 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/10 19:17:44 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define A 0
#define B 1

#include "../raytrace/draw.h"
#include "../lighting/lighting.h"

t_intersect	ray_intersects_triangle(t_xyz *viewpoint, t_xyz ray, t_triangle *triangle)
{
	t_intersect	intersect;
	t_xyz		edge1 = v_subtract(*triangle->b, *triangle->a);
	t_xyz		edge2 = v_subtract(*triangle->c, *triangle->a);
	t_xyz		ray_cross_e2 = v_cross(ray, edge2);
	double		det = v_dot(edge1, ray_cross_e2);

	intersect = new_intersect();
	if (fabs(det) < TOLERANCE)
		return (intersect);
	double	inv_det = 1.0 / det;
	t_xyz	s = v_subtract(*viewpoint, *triangle->a);
	double	u = inv_det * v_dot(s, ray_cross_e2);
	if (u < 0 || u > 1)
		return (intersect);

	t_xyz	s_cross_e1 = v_cross(s, edge1);
	double	v = inv_det * v_dot(ray, s_cross_e1);
	if (v < 0 || u + v > 1)
		return (intersect);

	double	t = inv_det * v_dot(edge2, s_cross_e1);
	if (t < TOLERANCE)
		return (intersect);

	intersect.distance = t;
	return ((t_intersect){true,
		v_add(*viewpoint, v_scale(ray, intersect.distance)),
		triangle->colour, intersect.distance, triangle,
		TRIANGLE, triangle->material});
}
