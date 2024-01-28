/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_checks.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:15:03 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/19 20:15:03 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"

bool	intersects_sphere(t_xyz intersect_point, t_xyz light_xyz,
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

bool	intersects_plane(t_xyz intersect_point, t_xyz light_xyz,
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

bool	intersects_cylinder(t_xyz intersect_point, t_xyz light_xyz,
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
