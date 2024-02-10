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
#define H 0
#define S 1
#define Q 2

#include "../raytrace/draw.h"
#include "../lighting/lighting.h"

t_intersect	ray_intersects_triangle(t_xyz *viewpoint, t_xyz ray, t_triangle *triangle)
{
	t_intersect	intersect;
	t_xyz		normal;
	t_xyz		side[2];
	t_xyz		vec[3];
	double		var[2];

	intersect = new_intersect();
	normal = triangle_normal(triangle);
	if (fabs(v_dot(normal, ray)) < TOLERANCE)
		return (intersect);
	else if (fabs(v_dot(normal, ray)) < 0)
		normal = v_invert(normal);
	side[A] = v_subtract(*triangle->b, *triangle->a);
	side[B] = v_subtract(*triangle->c, *triangle->a);
	vec[H] = v_subtract(*viewpoint, *triangle->a);
	vec[S] = v_cross(vec[H], side[B]);
	vec[Q] = v_cross(vec[S], side[A]);
	var[0] = v_dot(vec[S], v_cross(side[A], normal));
	if (fabs(var[0]) > 1)
		return (intersect);
	var[1] = v_dot(v_scale(ray, 1.0 / v_dot(normal, side[B])), vec[Q]);
	if (fabs(var[1]) > 1 || var[0] + var[1] > 1)
		return (intersect);
	intersect.distance = v_dot(side[B], vec[Q]) / v_dot(ray, vec[Q]);
	if (intersect.distance < TOLERANCE)
		return (intersect);
	return ((t_intersect){true,
		v_add(*viewpoint, v_scale(ray, intersect.distance)),
		triangle->colour, intersect.distance, triangle,
		TRIANGLE, triangle->material});
}
