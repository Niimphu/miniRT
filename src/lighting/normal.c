/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:22:33 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/15 19:11:33 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"
#include "../maths/matrix.h"

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

t_xyz cone_normal(t_cone *co, t_xyz point)
{
	t_xyz	t_to_i;
	double	angle;
	double	theta;

	theta = atan(co->radius / co->height);
	t_to_i = v_normalize(v_subtract(point, *co->centre));
	angle = angle_between(v_invert(*co->axis), t_to_i);
	if (fabs(theta - angle) > 1e-1)
		return (v_invert(*co->axis));
	t_xyz	perp = v_normalize(v_cross(t_to_i, *co->axis));
	t_xyz	normal = v_cross(perp, t_to_i);
	return (v_normalize(normal));
}

// double calculate_angle_at_p(Vector2D c, Vector2D i, Vector2D p) {
//     // Calculate the lengths of sides CP and CI
//     double cp_length = sqrt((p.x - c.x) * (p.x - c.x) + (p.y - c.y) * (p.y - c.y));
//     double ci_length = sqrt((i.x - c.x) * (i.x - c.x) + (i.y - c.y) * (i.y - c.y));
    
//     // Calculate the cosine of the angle at P using the law of cosines
//     double cos_angle_p = ((ci_length * ci_length) + (cp_length * cp_length) - (ip_length * ip_length)) / (2 * ci_length * cp_length);
    
//     // Return the angle at P in degrees
//     return acos(cos_angle_p) * 180 / M_PI; // Convert angle from radians to degrees
// }