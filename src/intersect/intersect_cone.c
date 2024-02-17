/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:41:51 by Kekuhne           #+#    #+#             */
/*   Updated: 2024/02/15 19:27:28 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define A 0
#define B 1
#define C 2

#include "../raytrace/draw.h"
#include "../maths/matrix.h"
#include "transform.h"

t_intersect			ray_intersects_sides(t_cone *cone,
						t_location_transformation_information_station t);
static t_intersect	ray_intersects_disc(t_cone *cone,
						t_location_transformation_information_station t);
static t_xyz		get_distances(t_cone *cone,
						t_location_transformation_information_station t);
t_intersect			validest(t_intersect side, t_intersect disc);

t_intersect	ray_intersects_cone(t_xyz *viewpoint, t_xyz ray, t_cone *cone)
{
	t_location_transformation_information_station	t;
	t_intersect										side;
	t_intersect										disc;
	t_intersect										intersection;

	intersection = new_intersect();
	t = new_transform(*cone->axis, *cone->centre, ray, *viewpoint);
	side = ray_intersects_sides(cone, t);
	disc = ray_intersects_disc(cone, t);
	if (!side.valid && !disc.valid)
		return (intersection);
	intersection = validest(side, disc);
	intersection.point = v_add(*viewpoint, v_scale(ray, intersection.distance));
	intersection.valid = true;
	intersection.shape = cone;
	intersection.type = CONE;
	intersection.material = cone->material;
	intersection.colour = cone->colour;
	return (intersection);
}

t_intersect	validest(t_intersect side, t_intersect disc)
{
	t_intersect	intersection;

	if (side.valid && disc.valid)
	{
		if (side.distance < disc.distance)
			intersection = side;
		else
			intersection = disc;
	}
	else if (side.valid)
		intersection = side;
	else
		intersection = disc;
	return (intersection);
}

t_intersect	ray_intersects_sides(t_cone *cone,
			t_location_transformation_information_station t)
{
	t_intersect	intersect;
	t_xyz		distances;

	intersect = new_intersect();
	distances = get_distances(cone, t);
	if (distances.x > TOLERANCE)
	{
		intersect.distance = distances.x;
		intersect.point = v_add(t.local_viewpoint,
				v_scale(t.local_ray, distances.x));
		if (intersect.point.y < 0 && intersect.point.y > -cone->height)
			return (intersect.valid = true, intersect);
	}
	if (distances.y > TOLERANCE)
	{
		intersect.distance = distances.y;
		intersect.point = v_add(t.local_viewpoint,
				v_scale(t.local_ray, distances.y));
		if (intersect.point.y < 0 && intersect.point.y > -cone->height)
			return (intersect.valid = true, intersect);
	}
	return (intersect);
}

static t_intersect	ray_intersects_disc(t_cone *cone,
					t_location_transformation_information_station t)
{
	t_xyz		disk_center;
	t_xyz		p;
	t_intersect	intersect;

	intersect = new_intersect();
	disk_center = (t_xyz){0, -cone->height, 0};
	intersect.distance = v_dot(v_subtract(disk_center, t.local_viewpoint),
			(t_xyz){0, 1, 0})
		/ v_dot(t.local_ray, (t_xyz){0, 1, 0});
	p = v_add(t.local_viewpoint, v_scale(t.local_ray, intersect.distance));
	if (p2p_distance(disk_center, p) < cone->radius
		&& intersect.distance > TOLERANCE)
		intersect.valid = true;
	return (intersect);
}

static t_xyz	get_distances(t_cone *cone,
					t_location_transformation_information_station t)
{
	double	discr_vars[3];
	double	discriminant;
	t_xyz	result;

	discr_vars[A] = pow(t.local_ray.x, 2) + pow(t.local_ray.z, 2)
		- (pow(t.local_ray.y, 2) * cone->theta);
	discr_vars[B] = (2 * t.local_viewpoint.x * t.local_ray.x)
		+ (2 * t.local_viewpoint.z * t.local_ray.z)
		- (2 * t.local_viewpoint.y * t.local_ray.y * cone->theta);
	discr_vars[C] = pow(t.local_viewpoint.x, 2) + pow(t.local_viewpoint.z, 2)
		- (pow(t.local_viewpoint.y, 2) * cone->theta);
	discriminant = discr_vars[B] * discr_vars[B] - 4 * discr_vars[A]
		* discr_vars[C];
	result = (t_xyz){0};
	if (discriminant < 0)
		return (result);
	if (discriminant < TOLERANCE)
		return (result.x = -discr_vars[B] / (2 * discr_vars[A]), result);
	result.x = (-discr_vars[B] - sqrt(discriminant)) / (2 * discr_vars[A]);
	result.y = (-discr_vars[B] + sqrt(discriminant)) / (2 * discr_vars[A]);
	return (result);
}
