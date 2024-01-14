/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 19:32:29 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/13 19:32:29 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "draw.h"

#define DTOLERANCE 0.00001

t_intersect	check_shadows(t_scene *scene, t_xyz light_point,
					t_intersect intersect)
{
	intersect = intersects_sphere(intersect.point, light_point, scene->spheres,
			intersect);
	if (intersect.in_shadow)
		return (intersect);
	intersect = intersects_plane(intersect.point, light_point,
			scene->planes, intersect);
//	if (intersects_sphere(intersect.point, light_point, scene->spheres,
//			intersect)
//		|| intersects_plane(intersect.point, light_point, scene->planes))
//		return (intersect.in_shadow = true, intersect);
	return (intersect);
}

t_intersect	intersects_sphere(t_xyz intersect_point, t_xyz light_xyz,
					t_list *spheres, t_intersect intersect)
{
	t_sphere	*sphere;
	t_intersect	check;
	t_xyz		to_light;

	to_light = v_normalize(v_subtract(light_xyz, intersect_point));
	intersect.light_distance = v_length(v_subtract(light_xyz, intersect_point));
	while (spheres)
	{
		sphere = (t_sphere *)spheres->content;
		check = ray_interects_sphere(&intersect_point, to_light, sphere);
		if (check.valid && check.distance > DTOLERANCE
			&& (check.distance < p2p_distance(intersect_point, light_xyz)))
			return (intersect.in_shadow = true, intersect);
		spheres = spheres->next;
	}
	return (intersect);
}

t_intersect	intersects_plane(t_xyz intersect_point, t_xyz light_xyz,
		t_list *planes, t_intersect intersect)
{
	t_plane		*plane;
	t_intersect	check;
	t_xyz		to_light;

	to_light = v_normalize(v_subtract(light_xyz, intersect_point));
	intersect.light_distance = v_length(v_subtract(light_xyz, intersect_point));
	while (planes)
	{
		plane = (t_plane *)planes->content;
		check = ray_intersects_plane(&intersect_point, to_light, plane);
		if (check.valid && check.distance > DTOLERANCE
			&& (check.distance < p2p_distance(intersect_point, light_xyz)))
			return (intersect.in_shadow = true, intersect);
		planes = planes->next;
	}
	return (intersect);
}
