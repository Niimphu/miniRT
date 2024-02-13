/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:41:51 by Kekuhne           #+#    #+#             */
/*   Updated: 2024/02/10 17:48:33 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define A 0
#define B 1
#define C 2

#include "../raytrace/draw.h"
#include "../maths/matrix.h"
#include "transform.h"

double			get_cone_distance(t_cone *cone,
					t_location_transformation_information_station t);
static double	ray_intersects_disc(t_cone *cone,
					t_location_transformation_information_station t);
static double	closest_intersection(t_cone *cone,
					t_location_transformation_information_station t);

t_intersect	ray_intersects_cone(t_xyz *viewpoint, t_xyz ray, t_cone *cone)
{
	t_location_transformation_information_station	t;
	t_intersect										intersection;

	intersection = new_intersect();
	t = new_transform(*cone->axis, *cone->centre, ray, *viewpoint);
	intersection.distance = get_cone_distance(cone, t);
	if (intersection.distance < TOLERANCE)
		intersection.distance = ray_intersects_disc(cone, t);
	if (intersection.distance < TOLERANCE)
		return (intersection);
	intersection.point = v_add(*viewpoint, v_scale(ray, intersection.distance));
	intersection.valid = true;
	intersection.shape = cone;
	intersection.type = CONE;
	intersection.material = cone->material;
	intersection.colour = cone->colour;
	return (intersection);
}

double	get_cone_distance(t_cone *cone,
			t_location_transformation_information_station t)
{
	double	distance;
	double	intersection_y;

	distance = closest_intersection(cone, t);
	if (distance >= TOLERANCE)
	{
		intersection_y = t.local_viewpoint.y + t.local_ray.y * distance;
		if (intersection_y <= 0 && intersection_y >= -cone->height)
			return (distance);
	}
	return (-1);
}

static double	ray_intersects_disc(t_cone *cone,
					t_location_transformation_information_station t)
{
	t_xyz	disk_center;
	t_xyz	p;
	double	dist;

	disk_center = (t_xyz){0, 0 - cone->height, 0};
	dist = v_dot(v_subtract(disk_center, t.local_viewpoint), (t_xyz){0, 1, 0})
		/ v_dot(t.local_ray, (t_xyz){0, 1, 0});
	p = v_add(t.local_viewpoint, v_scale(t.local_ray, dist));
	if (p2p_distance(disk_center, p) + TOLERANCE < cone->radius
		&& dist > TOLERANCE)
		return (p2p_distance(t.local_viewpoint, p));
	else
		return (-1);
}

static double	closest_intersection(t_cone *cone,
					t_location_transformation_information_station t)
{
	double	discr_vars[4];
	double	x1;
	double	x2;
	double	theta;

	theta = pow(cone->radius / cone->height, 2);
	discr_vars[A] = pow(t.local_ray.x, 2) + pow(t.local_ray.z, 2)
		- (pow(t.local_ray.y, 2) * theta);
	discr_vars[B] = (2 * t.local_viewpoint.x * t.local_ray.x)
		+ (2 * t.local_viewpoint.z * t.local_ray.z)
		- (2 * t.local_viewpoint.y * t.local_ray.y * theta);
	discr_vars[C] = pow(t.local_viewpoint.x, 2) + pow(t.local_viewpoint.z, 2)
		- (pow(t.local_viewpoint.y, 2) * theta);
	discr_vars[3] = discr_vars[B] * discr_vars[B] - 4 * discr_vars[A]
		* discr_vars[C];
	if (discr_vars[3] < 0)
		return (-1);
	x1 = (-discr_vars[B] - sqrt(discr_vars[3])) / (2 * discr_vars[A]);
	x2 = (-discr_vars[B] + sqrt(discr_vars[3])) / (2 * discr_vars[A]);
	if (x1 <= x2 && x1 >= 0)
		return (x1);
	else if (x2 < x1 && x2 >= 0)
		return (x2);
	return (-1);
}
