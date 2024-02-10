/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:41:51 by Kekuhne           #+#    #+#             */
/*   Updated: 2024/02/09 22:49:41 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define A 0
#define B 1
#define C 2

#include "../raytrace/draw.h"
#include "../maths/matrix.h"

#include "../printer/printer.h"

double	cone_local_intersect(t_xyz local_viewpoint, t_xyz local_ray, t_cone *cn)
{
	double	t1;
	double	t2;
	double	discr_vars[4];
	double	theta;

	theta = atan(cn->radius / cn->height);
	discr_vars[0] = local_ray.x * local_ray.x + local_ray.z * local_ray.z - (local_ray.y * local_ray.y) * theta;
	discr_vars[1] = 2 * (local_viewpoint.x * local_ray.x + local_viewpoint.z * local_ray.z - (local_viewpoint.y * local_ray.y) * theta);
	discr_vars[2] = local_viewpoint.x * local_viewpoint.x + local_viewpoint.z * local_viewpoint.z - (local_viewpoint.y * local_viewpoint.y) * theta;
	discr_vars[3] = discr_vars[1] * discr_vars[1] - 4 * discr_vars[0] * discr_vars[2];
	if (discr_vars[3] < 0)
		return (-1);
	t1 = (-discr_vars[1] - sqrt(discr_vars[3])) / (2 * discr_vars[0]);
	t2 = (-discr_vars[1] + sqrt(discr_vars[3])) / (2 * discr_vars[0]);
	if (t1 <= t2 && t1 >= 0)
	{
		if (local_viewpoint.y + local_ray.y * t1 > cn->height * -1 && local_viewpoint.y + local_ray.y * t1 < 0)
			return (t1);
	} 
	else if (t2 < t1 && t2 >= 0)
	{
		if (local_viewpoint.y + local_ray.y * t2 > cn->height * -1 && local_viewpoint.y + local_ray.y * t2 < 0)
			return (t2);
	}
	return (-1);
}

double	cone_disk_intersect(t_cone *co, t_xyz *viewpoint, t_xyz ray)
{
	t_xyz	disk_center;
	t_xyz	p;
	double	dist;
	
	disk_center = (t_xyz){0, 0 - co->height, 0};
	dist = v_dot(v_subtract(disk_center, *viewpoint), (t_xyz){0, 1, 0}) / v_dot(ray, (t_xyz){0, 1, 0});
	p = v_add(*viewpoint, v_scale(ray, dist));
	if (p2p_distance(disk_center, p) + TOLERANCE < co->radius && dist > TOLERANCE)
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
	if (intersection.distance < TOLERANCE)
		intersection.distance = cone_disk_intersect(co, &local_viewpoint, local_ray);
	if (intersection.distance < TOLERANCE)
		return (intersection);
	intersection.point = v_add(*viewpoint, v_scale(ray, intersection.distance));
	intersection.valid = true;
	intersection.shape = co;
	intersection.type = CONE;
	intersection.material = co->material;
	intersection.colour = co->colour;
	return (intersection);
}
