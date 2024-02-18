/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_checks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:15:03 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/13 16:56:47 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"

bool	intersects_any_sphere(t_xyz intersect_point, t_xyz light_xyz,
			t_list *spheres, t_xyz to_light)
{
	t_sphere	*sphere;
	t_intersect	check;

	while (spheres)
	{
		sphere = (t_sphere *)spheres->content;
		check = ray_intersects_sphere(&intersect_point, to_light, sphere);
		if (check.valid && check.distance > TOLERANCE
			&& (check.distance < p2p_distance(intersect_point, light_xyz)))
			return (true);
		spheres = spheres->next;
	}
	return (false);
}

bool	intersects_any_plane(t_xyz intersect_point, t_xyz light_xyz,
			t_list *planes, t_xyz to_light)
{
	t_plane		*plane;
	t_intersect	check;

	while (planes)
	{
		plane = (t_plane *)planes->content;
		check = ray_intersects_plane(&intersect_point, to_light, plane);
		if (check.valid && check.distance > TOLERANCE
			&& (check.distance < p2p_distance(intersect_point, light_xyz)))
			return (true);
		planes = planes->next;
	}
	return (false);
}

bool	intersects_any_cylinder(t_xyz intersect_point, t_xyz light_xyz,
				t_list *cylinders, t_xyz to_light)
{
	t_cylinder	*cylinder;
	t_intersect	check;

	while (cylinders)
	{
		cylinder = (t_cylinder *)cylinders->content;
		check = ray_intersects_cylinder(&intersect_point, to_light, cylinder);
		if (check.valid && check.distance > TOLERANCE
			&& (check.distance < p2p_distance(intersect_point, light_xyz)))
			return (true);
		cylinders = cylinders->next;
	}
	return (false);
}

bool	intersects_any_cone(t_xyz intersect_point, t_xyz light_xyz,
				t_list *cones, t_xyz to_light)
{
	t_cone		*cone;
	t_intersect	check;

	while (cones)
	{
		cone = (t_cone *)cones->content;
		check = ray_intersects_cone(&intersect_point, to_light, cone);
		if (check.valid && check.distance > TOLERANCE
			&& (check.distance < p2p_distance(intersect_point, light_xyz)))
			return (true);
		cones = cones->next;
	}
	return (false);
}

bool	intersects_any_triangle(t_xyz intersect_point, t_xyz light_xyz,
							t_list *triangles, t_xyz to_light)
{
	t_triangle	*triangle;
	t_intersect	check;

	while (triangles)
	{
		triangle = (t_triangle *)triangles->content;
		check = ray_intersects_triangle(&intersect_point, to_light, triangle);
		if (check.valid && check.distance > TOLERANCE
			&& (check.distance + TOLERANCE
				< p2p_distance(intersect_point, light_xyz)))
			return (true);
		triangles = triangles->next;
	}
	return (false);
}
