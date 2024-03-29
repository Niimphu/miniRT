/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:08:30 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/10 19:01:26 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define A 0
#define B 1
#define C 2

#define TOP 0
#define BOT 1

#include "../maths/matrix.h"
#include "transform.h"
#include "intersect.h"

static t_intersect	ray_intersects_tube(t_xyz viewpoint, t_xyz ray,
						t_cylinder *cylinder,
						t_location_transformation_information_station t);
static t_intersect	ray_intersects_caps(t_xyz viewpoint, t_xyz ray,
						t_cylinder *cylinder,
						t_location_transformation_information_station t);
static t_xyz		get_tube_distance(t_xyz viewpoint, t_xyz ray,
						t_cylinder *cylinder);
static t_intersect	get_cap_intersection(t_xyz centre, t_cylinder *cylinder,
						t_location_transformation_information_station t);

t_intersect	ray_intersects_cylinder(t_xyz *viewpoint, t_xyz ray,
				t_cylinder *cylinder)
{
	t_location_transformation_information_station	t;
	t_intersect										intersection;
	t_intersect										tube;
	t_intersect										disc;

	t = new_transform(*cylinder->axis, *cylinder->centre, ray, *viewpoint);
	tube = ray_intersects_tube(*viewpoint, ray, cylinder, t);
	disc = ray_intersects_caps(*viewpoint, ray, cylinder, t);
	intersection = get_closer_buddy(tube, disc);
	if (!intersection.valid)
		return (new_intersect());
	intersection.shape = cylinder;
	intersection.type = CYLINDER;
	intersection.colour = cylinder->colour;
	intersection.material = cylinder->material;
	return (intersection);
}

static t_intersect	ray_intersects_tube(t_xyz viewpoint, t_xyz ray,
						t_cylinder *cylinder,
						t_location_transformation_information_station t)
{
	t_intersect	intersect;
	t_xyz		distances;

	distances = get_tube_distance(t.local_viewpoint,
			t.local_ray, cylinder);
	intersect = closest_side(distances, cylinder, t);
	intersect.point = v_add(viewpoint,
			v_scale(ray, intersect.distance - TOLERANCE));
	return (intersect);
}

static t_intersect	ray_intersects_caps(t_xyz viewpoint, t_xyz ray,
						t_cylinder *cylinder,
						t_location_transformation_information_station t)
{
	int			closest;
	t_xyz		centre[2];
	t_intersect	intersect[2];

	centre[TOP] = (t_xyz){0, cylinder->height / 2.0, 0};
	centre[BOT] = (t_xyz){0, cylinder->height / -2.0, 0};
	if (p2p_distance(t.local_viewpoint, centre[TOP])
		< p2p_distance(t.local_viewpoint, centre[BOT]))
		closest = TOP;
	else
		closest = BOT;
	intersect[TOP] = get_cap_intersection(centre[TOP], cylinder, t);
	intersect[TOP].point = v_add(viewpoint,
			v_scale(ray, intersect[TOP].distance));
	intersect[BOT] = get_cap_intersection(centre[BOT], cylinder, t);
	intersect[BOT].point = v_add(viewpoint,
			v_scale(ray, intersect[BOT].distance));
	if (intersect[TOP].valid && intersect[BOT].valid)
		return (intersect[closest]);
	if (intersect[TOP].valid)
		return (intersect[TOP]);
	return (intersect[BOT]);
}

static t_xyz	get_tube_distance(t_xyz viewpoint, t_xyz ray,
			t_cylinder *cylinder)
{
	t_xyz	result;
	double	vars[3];
	double	discriminant;
	t_xyz	axis;

	axis = (t_xyz){0, 1, 0};
	vars[A] = v_dot(ray, ray) - pow(v_dot(ray, axis), 2);
	vars[B] = 2 * (v_dot(viewpoint, ray) - v_dot(ray, axis) * v_dot(viewpoint,
				axis));
	vars[C] = v_dot(viewpoint, viewpoint) - pow(v_dot(viewpoint, axis), 2)
		- pow(cylinder->radius, 2);
	discriminant = vars[B] * vars[B] - 4 * vars[A] * vars[C];
	result = (t_xyz){0};
	if (discriminant < 0)
		return (result);
	if (discriminant < TOLERANCE)
		return (result.x = -vars[B] / 2.0 * vars[A], result);
	result.x = (-vars[1] - sqrt(discriminant)) / (2 * vars[0]);
	result.y = (-vars[1] + sqrt(discriminant)) / (2 * vars[0]);
	return (result);
}

static t_intersect	get_cap_intersection(t_xyz centre, t_cylinder *cylinder,
				t_location_transformation_information_station t)
{
	t_intersect	intersect;
	double		dist;

	intersect = new_intersect();
	dist = v_dot(v_subtract(centre, t.local_viewpoint), (t_xyz){0, 1, 0})
		/ v_dot(t.local_ray, (t_xyz){0, 1, 0});
	intersect.point = v_add(t.local_viewpoint, v_scale(t.local_ray, dist));
	if (p2p_distance(centre, intersect.point)
		+ TOLERANCE < cylinder->radius && dist > TOLERANCE)
	{
		intersect.distance = p2p_distance(t.local_viewpoint, intersect.point);
		if (intersect.distance > TOLERANCE)
			intersect.valid = true;
	}
	return (intersect);
}
