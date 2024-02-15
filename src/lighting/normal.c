/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 18:22:33 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/15 16:36:33 by Kekuhne          ###   ########.fr       */
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

	t_to_i = v_normalize(v_subtract(point, *co->centre));
	printf("t_to_i = x = %f,y = %f,z= %f\n, point = x = %f,y = %f,z= %f\n centre = x = %f,y = %f,z= %f\n", t_to_i.x, t_to_i.y, t_to_i.z, point.x, point.y, point.z, co->centre->x, co->centre->y, co->centre->z);
	angle = angle_between(*co->axis, t_to_i);
	if (angle < co->theta + TOLERANCE)
		return (*co->axis);
	angle = angle * (180 / M_PI);
	double theta = co->theta * (180 / M_PI);
	printf("angle = %f, theta = %f\n", angle, theta);
	exit(1);
	return (v_normalize(point));
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