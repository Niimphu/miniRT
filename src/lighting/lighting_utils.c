/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:12:59 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/13 16:37:26 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lighting.h"

t_xyz	get_surface_normal(t_intersect intersect)
{
	if (intersect.type == SPHERE)
		return (sphere_normal(intersect.shape, intersect.point));
	if (intersect.type == PLANE)
		return (plane_normal(intersect.shape));
	if (intersect.type == CYLINDER)
		return (cylinder_normal(intersect.shape, intersect.point));
	if (intersect.type == TRIANGLE)
		return (triangle_normal(intersect.shape));
	if (intersect.type == CONE)
		return (cone_normal(intersect.shape, intersect.point));
	return ((t_xyz){0});
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

bool	intersects_any_shape(t_xyz intersection, t_xyz light_point,
			t_scene *scene, t_xyz light_direction)
{
	return (intersects_any_sphere(intersection, light_point,
			scene->spheres, light_direction)
		|| intersects_any_plane(intersection,
			light_point, scene->planes, light_direction)
		|| intersects_any_cylinder(intersection, light_point,
			scene->cylinders, light_direction)
		|| intersects_any_cone(intersection, light_point,
			scene->cones, light_direction)
		|| intersects_any_triangle(intersection, light_point,
			scene->triangles, light_direction));
}
