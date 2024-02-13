/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:22:33 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/13 16:29:33 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"

t_xyz	sphere_normal(t_sphere *sphere, t_xyz point)
{
	return (v_normalize(v_subtract(point, *sphere->centre)));
}

t_xyz	plane_normal(t_plane *plane)
{
	return (*plane->norm);
}

t_xyz	cylinder_normal(t_cylinder *cylinder, t_xyz point)
{
	t_xyz	to_surface;
	double	to_surface_axis_dot;
	double	axis2;
	t_xyz	projected;
	t_xyz	closest_point;

	to_surface = v_subtract(point, *cylinder->centre);
	to_surface_axis_dot = v_dot(*cylinder->axis, to_surface);
	axis2 = v_dot(*cylinder->axis, *cylinder->axis);
	projected = v_scale(*cylinder->axis, to_surface_axis_dot / axis2);
	closest_point = v_add(*cylinder->centre, projected);
	if (p2p_distance(closest_point, point) < cylinder->radius)
		return (v_normalize(projected));
	else
		return (v_normalize(v_subtract(to_surface, projected)));
}

t_xyz	triangle_normal(t_triangle *triangle)
{
	t_xyz	a_b;
	t_xyz	a_c;
	t_xyz	normal;

	a_b = v_subtract(*triangle->b, *triangle->a);
	a_c = v_subtract(*triangle->c, *triangle->a);
	normal = v_cross(a_b, a_c);
	return (v_normalize(normal));
}

t_xyz	cone_normal(t_cone *co, t_xyz point)
{
	double	r;
	t_xyz	normal;

	r = sqrt((point.x - co->centre->x) * (point.x - co->centre->x)
		+ (point.z - co->centre->z) * (point.z - co->centre->z));
	normal = (t_xyz){(point.x - co->centre->x), r
		* (co->radius / co->height), (point.z - co->centre->z)};
	return (v_normalize(normal));
}
