/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:28:24 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/14 17:54:44 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "draw.h"

t_intersect	get_closest_sphere(t_xyz viewpoint, t_xyz ray, t_list *spheres);
t_intersect	get_closest_plane(t_xyz viewpoint, t_xyz ray, t_list *planes);

t_intersect	get_closest_shape(t_xyz viewpoint, t_xyz ray, t_scene *scene)
{
	t_intersect	closest_sphere;
	t_intersect	closest_plane;
	t_intersect	closest_cylinder;

	closest_sphere = get_closest_sphere(viewpoint, ray, scene->spheres);
	closest_plane = get_closest_plane(viewpoint, ray, scene->planes);
	if (!closest_sphere.valid && !closest_plane.valid)
		return (new_intersect());
	if (!closest_sphere.valid && closest_plane.valid)
		return (closest_plane);
	if (closest_sphere.valid && !closest_plane.valid)
		return (closest_sphere);
	if (closest_plane.distance < closest_sphere.distance)
		return (closest_plane);
	(void)closest_cylinder;
	return (closest_sphere);
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
		new = ray_interects_sphere(&viewpoint, ray, sphere);
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
