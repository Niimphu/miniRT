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

#define S 0
#define RAY_X_E1 1
#define S_X_E0 2

#define U 0
#define V 1

#include "../raytrace/draw.h"
#include "../lighting/lighting.h"

t_intersect	triangle_intersection(t_intersect intersect, t_xyz viewpoint,
				t_xyz ray, t_triangle *triangle);

t_intersect	ray_intersects_triangle(t_xyz *viewpoint, t_xyz ray,
				t_triangle *triangle)
{
	t_intersect	intersect;
	t_xyz		edge[2];
	double		var[2];
	t_xyz		vec[3];
	double		det;

	edge[0] = v_subtract(*triangle->b, *triangle->a);
	edge[1] = v_subtract(*triangle->c, *triangle->a);
	vec[RAY_X_E1] = v_cross(ray, edge[1]);
	det = v_dot(edge[0], vec[RAY_X_E1]);
	intersect = new_intersect();
	if (fabs(det) < TOLERANCE)
		return (intersect);
	det = 1.0 / det;
	vec[S] = v_subtract(*viewpoint, *triangle->a);
	var[U] = det * v_dot(vec[S], vec[RAY_X_E1]);
	vec[S_X_E0] = v_cross(vec[S], edge[0]);
	var[V] = det * v_dot(ray, vec[S_X_E0]);
	if (var[U] < 0 || var[U] > 1 || var[V] < 0 || var[U] + var[V] > 1)
		return (intersect);
	intersect.distance = det * v_dot(edge[1], vec[S_X_E0]);
	if (intersect.distance < TOLERANCE)
		return (intersect);
	return (triangle_intersection(intersect, *viewpoint, ray, triangle));
}

t_intersect	triangle_intersection(t_intersect intersect, t_xyz viewpoint,
				t_xyz ray, t_triangle *triangle)
{
	intersect.valid = true;
	intersect.point = v_add(viewpoint, v_scale(ray, intersect.distance));
	intersect.colour = triangle->colour;
	intersect.shape = triangle;
	intersect.type = TRIANGLE;
	intersect.material = triangle->material;
	return (intersect);
}
