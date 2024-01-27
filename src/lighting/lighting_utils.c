/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:12:59 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/23 17:12:59 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../maths/xyz.h"
#include "../../lib/miniRT.h"
#include "../intersect/intersect.h"

t_xyz	sphere_normal(t_sphere *sphere, t_xyz point);
t_xyz	plane_normal(t_plane *plane);
t_xyz	cylinder_normal(t_cylinder *cylinder, t_xyz point);

t_xyz	get_surface_normal(t_intersect intersect)
{
	if (intersect.type == SPHERE)
		return (sphere_normal(intersect.shape, intersect.point));
	if (intersect.type == PLANE)
		return (plane_normal(intersect.shape));
	if (intersect.type == CYLINDER)
		return (cylinder_normal(intersect.shape, intersect.point));
	return ((t_xyz){0});
}

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
	double	axis_l2;
	t_xyz	axis_parallel;
	t_xyz	surface_normal;

	to_surface = v_subtract(point, *cylinder->centre);
	to_surface_axis_dot = v_dot(*cylinder->axis, to_surface);
	axis_l2 = v_dot(*cylinder->axis, *cylinder->axis);
	axis_parallel = v_scale(*cylinder->axis, (to_surface_axis_dot / axis_l2));
	surface_normal = v_subtract(to_surface, axis_parallel);
	return (v_normalize(surface_normal));
}

t_xyz	get_halfway_vector(t_xyz intersection, t_xyz light_pos,
							t_xyz camera_pos)
{
	t_xyz	to_camera;
	t_xyz	to_light;
	t_xyz	halfway;

	to_camera = v_normalize(v_subtract(camera_pos, intersection));
	to_light = v_normalize(v_subtract(light_pos, intersection));
	halfway = v_normalize(v_add(to_light, to_camera));
	return (halfway);
}
