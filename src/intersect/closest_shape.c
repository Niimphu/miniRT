/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_shape.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:28:24 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/09 19:43:11 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/miniRT.h"
#include "../raytrace/draw.h"

t_intersect	get_closest_sphere(t_xyz viewpoint, t_xyz ray, t_list *spheres);
t_intersect	get_closest_plane(t_xyz viewpoint, t_xyz ray, t_list *planes);
t_intersect	get_closest_cylinder(t_xyz viewpoint, t_xyz ray, t_list *cylinders);
t_intersect	get_closest_cone(t_xyz viewpoint, t_xyz ray, t_list *cones);

/* t_intersect	get_closest_shape(t_xyz viewpoint, t_xyz ray, t_scene *scene)
{
	t_intersect	closest_sphere;
	t_intersect	closest_plane;
	t_intersect	closest_cylinder;
	t_intersect	closest_shape;

	closest_shape = new_intersect();
	closest_sphere = get_closest_sphere(viewpoint, ray, scene->spheres);
	closest_plane = get_closest_plane(viewpoint, ray, scene->planes);
	closest_cylinder = get_closest_cylinder(viewpoint, ray, scene->cylinders);
	closest_cone = get_closest_cone(viewpoint, ray, scene->cone);
	if (closest_sphere.valid)
		closest_shape = closest_sphere;
	if (closest_plane.valid && ((closest_plane.distance < closest_shape.distance
				&& closest_shape.valid) || !closest_shape.valid))
		closest_shape = closest_plane;
	if (closest_cylinder.valid && ((closest_cylinder.distance
				< closest_shape.distance && closest_shape.valid)
			|| !closest_shape.valid))
		closest_shape = closest_cylinder;
	return (closest_shape);
} */

t_intersect	get_closest_shape(t_xyz viewpoint, t_xyz ray, t_scene *scene)
{
	int			i;
	int			j;
	t_intersect	closest[4];
	t_intersect	closest_shape;
	
	i = 0;
	closest_shape = new_intersect();
	closest_shape.distance = -1;
	closest[0] = get_closest_sphere(viewpoint, ray, scene->spheres);
	closest[1] = get_closest_plane(viewpoint, ray, scene->planes);
	closest[2] = get_closest_cylinder(viewpoint, ray, scene->cylinders);
	closest[3] = get_closest_cone(viewpoint, ray, scene->cone);
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (closest[j].valid && ((closest[j].distance < closest[i].distance)
				|| !closest[i].valid))
				closest_shape = closest[j];
			j++;
		}
		i++;
	}
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

t_intersect	get_closest_cone(t_xyz viewpoint, t_xyz ray, t_list *cones)
{
	t_cone	*cone;
	t_intersect	closest;
	t_intersect	new;

	closest = new_intersect();
	while (cones)
	{
		cone = (t_cone *)cones->content;
		new = ray_intersects_cone(&viewpoint, ray, cone);
		if (!closest.valid || (new.valid && (new.distance < closest.distance)))
			closest = new;
		cones = cones->next;
	}
	return (closest);
}
