/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:28:24 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/12 19:28:24 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/miniRT.h"
#include "../raytrace/draw.h"

t_intersect	get_closest_sphere(t_xyz viewpoint, t_xyz ray, t_list *spheres);
t_intersect	get_closest_plane(t_xyz viewpoint, t_xyz ray, t_list *planes);
t_intersect	get_closest_cylinder(t_xyz viewpoint, t_xyz ray, t_list *cylinders);

t_intersect	get_closest_shape(t_xyz viewpoint, t_xyz ray, t_scene *scene)
{
	t_intersect	closest_sphere;
	t_intersect	closest_plane;
	t_intersect	closest_cylinder;
	t_intersect	closest_shape;

	closest_shape = new_intersect();
	closest_sphere = get_closest_sphere(viewpoint, ray, scene->spheres);
	closest_plane = get_closest_plane(viewpoint, ray, scene->planes);
	closest_cylinder = get_closest_cylinder(viewpoint, ray, scene->cylinders);
	if (closest_sphere.valid)
		closest_shape = closest_sphere;
	if (closest_plane.valid && (closest_plane.distance < closest_shape.distance
			|| !closest_shape.valid))
		closest_shape = closest_plane;
	if (closest_cylinder.valid && (closest_cylinder.distance
			< closest_shape.distance || !closest_shape.valid))
		closest_shape = closest_cylinder;
	return (closest_shape);
}

t_intersect	get_closest_sphere(t_xyz viewpoint, t_xyz ray, t_list *spheres)
{
	t_sphere	*sphere;
	t_intersect	closest;
	t_intersect	new;

	closest = new_intersect();
	while (spheres)
	{
		sphere = (t_sphere *)spheres->content;
		new = ray_intersects_sphere(&viewpoint, ray, sphere);
		if (!closest.valid || (new.valid && (new.distance < closest.distance)))
			closest = new;
		spheres = spheres->next;
	}
	return (closest);
}

t_intersect	get_closest_plane(t_xyz viewpoint, t_xyz ray, t_list *planes)
{
	t_plane		*plane;
	t_intersect	closest;
	t_intersect	new;

	closest = new_intersect();
	while (planes)
	{
		plane = (t_plane *)planes->content;
		new = ray_intersects_plane(&viewpoint, ray, plane);
		if (!closest.valid || (new.valid && (new.distance < closest.distance)))
			closest = new;
		planes = planes->next;
	}
	return (closest);
}

t_intersect	get_closest_cylinder(t_xyz viewpoint, t_xyz ray, t_list *cylinders)
{
	t_cylinder	*cylinder;
	t_intersect	closest;
	t_intersect	new;

	closest = new_intersect();
	while (cylinders)
	{
		cylinder = (t_cylinder *)cylinders->content;
		new = ray_intersects_cylinder(&viewpoint, ray, cylinder);
		if (!closest.valid || (new.valid && (new.distance < closest.distance)))
			closest = new;
		cylinders = cylinders->next;
	}
	return (closest);
}
