/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:41:51 by Kekuhne           #+#    #+#             */
/*   Updated: 2024/02/15 18:32:14 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define A 0
#define B 1
#define C 2

#include "../raytrace/draw.h"
#include "../maths/matrix.h"

#include "../printer/printer.h"

static double	cone_discr_vars(t_xyz local_viewpoint,
	t_xyz local_ray, t_cone *cn)
{
	double	discr_vars[4];
	double	t[2];

	discr_vars[A] = pow(local_ray.x, 2) + pow(local_ray.z, 2)
		- (pow(local_ray.y, 2) * cn->theta);
	discr_vars[B] = (2 * local_viewpoint.x * local_ray.x)
		+ (2 * local_viewpoint.z * local_ray.z)
		- (2 * local_viewpoint.y * local_ray.y * cn->theta);
	discr_vars[C] = pow(local_viewpoint.x, 2) + pow(local_viewpoint.z, 2)
		- (pow(local_viewpoint.y, 2) * cn->theta);
	discr_vars[3] = discr_vars[B] * discr_vars[B] - 4 * discr_vars[A]
		* discr_vars[C];
	if (discr_vars[3] < TOLERANCE)
		return (-1);
	t[0] = (-discr_vars[B] - sqrt(discr_vars[3])) / (2 * discr_vars[A]);
	t[1] = (-discr_vars[B] + sqrt(discr_vars[3])) / (2 * discr_vars[A]);
	if (t[0] <= t[1] && t[0] >= TOLERANCE)
		return (t[0]);
	else if (t[1] < t[0] && t[1] >= TOLERANCE)
		return (t[1]);
	return (-1);
}

double	cone_local_intersect(t_xyz local_viewpoint, t_xyz local_ray, t_cone *cn)
{
	double	t;
	double	intersection_y;

	t = cone_discr_vars(local_viewpoint, local_ray, cn);
	if (t >= TOLERANCE)
	{
		intersection_y = local_viewpoint.y + local_ray.y * t;
		if (intersection_y <= 0 && intersection_y >= -cn->height)
			return (t);
	}
	return (-1);
}

double	cone_disk_intersect(t_cone *co, t_xyz *viewpoint, t_xyz ray)
{
	t_xyz	disk_center;
	t_xyz	p;
	double	dist;

	disk_center = (t_xyz){0, 0 - co->height, 0};
	dist = v_dot(v_subtract(disk_center, *viewpoint), (t_xyz){0, 1, 0})
		/ v_dot(ray, (t_xyz){0, 1, 0});
	p = v_add(*viewpoint, v_scale(ray, dist));
	if (p2p_distance(disk_center, p) + TOLERANCE < co->radius
		&& dist > TOLERANCE)
		return (p2p_distance(*viewpoint, p));
	else
		return (-1);
}

t_intersect	ray_intersects_cone(t_xyz *viewpoint, t_xyz ray, t_cone *co)
{
	t_matrix	to_local;
	t_matrix	rotation;
	t_xyz		local_viewpoint;
	t_xyz		local_ray;
	t_intersect	intersection;
	double		rotation_angle;

	intersection = new_intersect();
	rotation_angle = angle_between(v_normalize(*co->axis), (t_xyz){0, 1, 0});
	rotation = create_rotation_matrix(v_cross(*co->axis, (t_xyz){0, 1, 0}), rotation_angle);
	to_local = local_matrix(*co->axis, *co->centre, rotation_angle);
	local_ray = v_matrix_mul(rotation, ray);
	local_viewpoint = v_matrix_mul(to_local, *viewpoint);
	intersection.distance = cone_local_intersect(local_viewpoint, local_ray, co);
	if (intersection.distance == -1)
		intersection.distance = cone_disk_intersect(co, &local_viewpoint, local_ray);
	if (intersection.distance == -1)
		return (intersection);
	intersection.point = v_add(*viewpoint, v_scale(ray, intersection.distance));
	intersection.valid = true;
	intersection.shape = co;
	intersection.type = CONE;
	intersection.material = co->material;
	intersection.colour = co->colour;
	return (intersection);
}
