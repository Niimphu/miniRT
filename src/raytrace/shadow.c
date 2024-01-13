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
	if (intersects_sphere(intersect.point, light_point, scene->spheres)
		|| intersects_plane(intersect.point, light_point, scene->planes))
		return (intersect.in_shadow = true, intersect);
	return (intersect);
}

bool	intersects_sphere(t_xyz intersect_point, t_xyz light_xyz,
					t_list *spheres)
{
	t_sphere	*sphere;
	t_intersect	check;
	t_xyz		to_light;

	while (spheres)
	{
		sphere = (t_sphere *)spheres->content;
		to_light = v_normalize(v_subtract(light_xyz, intersect_point));
		check = ray_interects_sphere(&intersect_point, to_light, sphere);
		if (check.valid && check.distance > DTOLERANCE
			&& (check.distance < p2p_distance(intersect_point, light_xyz)))
			return (true);
		spheres = spheres->next;
	}
	return (false);
}

bool	intersects_plane(t_xyz intersect_point, t_xyz light_xyz, t_list *planes)
{
	t_plane		*plane;
	t_intersect	check;
	t_xyz		to_light;

	while (planes)
	{
		plane = (t_plane *)planes->content;
		to_light = v_normalize(v_subtract(light_xyz, intersect_point));
		check = ray_intersects_plane(&intersect_point, to_light, plane);
		if (check.valid && check.distance > DTOLERANCE
			&& (check.distance < p2p_distance(intersect_point, light_xyz)))
			return (true);
		planes = planes->next;
	}
	return (false);
}
