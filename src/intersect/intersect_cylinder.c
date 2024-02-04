/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:08:30 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/02 17:45:55 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define A 0
#define B 1
#define C 2

#include "../raytrace/draw.h"
#include "../maths/matrix.h"

double	cyl_local_intersect(t_xyz local_viewpoint, t_xyz local_ray, t_cylinder *cl)
{
	double	t1;
	double	t2;
	double	discr_vars[4];

	discr_vars[0] = v_dot(local_ray, local_ray) - pow(v_dot(local_ray, (t_xyz){0, 1, 0}), 2);
	discr_vars[1] = 2 * (v_dot(local_viewpoint, local_ray) - v_dot(local_ray, (t_xyz){0, 1, 0}) * v_dot(local_viewpoint, (t_xyz){0, 1, 0}));
	discr_vars[2] = v_dot(local_viewpoint, local_viewpoint) - pow(v_dot(local_viewpoint, (t_xyz){0, 1, 0}), 2) - pow(cl->radius, 2);
	discr_vars[3] = discr_vars[1] * discr_vars[1] - 4 * discr_vars[0] * discr_vars[2];
	if (discr_vars[3] <= 0)
		return (-1);
	t1 = (-discr_vars[1] - sqrt(discr_vars[3])) / (2 * discr_vars[0]);
	t2 = (-discr_vars[1] + sqrt(discr_vars[3])) / (2 * discr_vars[0]);
	if (t1 <= t2 && t1 >= 0)
		return (t1);
	else if (t2 >= 0)
		return (t2);
	else
		return (-1);
}

t_xyz ray_intersects_cylinder_disk(t_xyz viewpoint, t_xyz ray, t_intersect intersection,  t_cylinder *cl)
{
	double distance_to_disk;
	distance_to_disk = (cl->height / 2.0) / fabs(ray.y);
	if (distance_to_disk >= 0)
	{
		// Calculate the intersection point on the disk
		t_xyz intersection_point;
		intersection_point= v_add(viewpoint, v_scale(ray, distance_to_disk));
		// Check if the intersection point is within the disk's radius
		if (pow(intersection_point.x, 2) + pow(intersection_point.z, 2) <= pow(cl->radius, 2))
		{
			// Update the intersection information
			intersection.point = intersection_point;
			intersection.distance = distance_to_disk;
			intersection.shape = cl;
			intersection.type = CYLINDER;
			intersection.colour = cl->colour;
			intersection.valid = true;
			return (intersection_point);
		}
	}
	intersection.valid = false;
	return (intersection.point);
}

t_intersect	ray_intersects_cylinder(t_xyz *viewpoint, t_xyz ray, t_cylinder *cl)
{
	t_matrix	to_local;
	t_matrix	rotation;
	t_matrix	to_world;
	t_xyz		local_viewpoint;
	t_xyz		local_ray;
	t_intersect	intersection;
	double		rotation_angle;

	intersection = new_intersect();
	rotation_angle = angle_between(v_normalize(*cl->axis),(t_xyz){0,1,0});
	rotation = create_rotation_matrix(v_cross(*cl->axis, (t_xyz){0,1,0}), rotation_angle);
	to_local = local_matrix(*cl->axis, *cl->centre, rotation_angle);
	to_world = world_matrix(*cl->axis, *cl->centre, rotation_angle);
	local_ray = v_matrix_mul(rotation, ray);
	local_viewpoint = v_matrix_mul(to_local, *viewpoint);
	intersection.distance = cyl_local_intersect(local_viewpoint, local_ray, cl);
	if (intersection.distance < 0)
		return (intersection);
	intersection.point = v_add(local_viewpoint, v_scale(local_ray, intersection.distance));
	if (intersection.point.y < cl->height / 2 && intersection.point.y > cl->height / -2)
	{
		intersection.point = v_matrix_mul(to_world, intersection.point);
		intersection.point = v_add(*viewpoint, v_scale(ray, intersection.distance - TOLERANCE));
		intersection.valid = true;
	}
	else
	{
		t_xyz top_centre = (t_xyz) {0, cl->height / 2.0, 0};
		t_xyz bot_centre = (t_xyz) {0, cl->height / -2.0, 0};
		double dist_top =
				v_dot(v_subtract(top_centre, local_viewpoint), (t_xyz){0, 1, 0}) / v_dot(local_ray, (t_xyz) {0, 1, 0});
		double dist_bot =
				v_dot(v_subtract(bot_centre, local_viewpoint), (t_xyz){0, 1, 0}) / v_dot(local_ray, (t_xyz) {0, 1, 0});
		t_xyz top_point = v_add(local_viewpoint, v_scale(local_ray, dist_top));
		t_xyz bot_point = v_add(local_viewpoint, v_scale(local_ray, dist_bot));
		if (p2p_distance(top_centre, top_point) <= cl->radius) {
			intersection.point = v_matrix_mul(to_world, top_point);
			intersection.distance = p2p_distance(*viewpoint, intersection.point);
			intersection.valid = true;
		}
		if (p2p_distance(bot_centre, bot_point) <= cl->radius) {
			intersection.point = v_matrix_mul(to_world, bot_point);
			intersection.distance = p2p_distance(*viewpoint, intersection.point);
			intersection.valid = true;
		}
	}
	intersection.shape = cl;
	intersection.type = CYLINDER;
	intersection.colour = cl->colour;
	return (intersection);
}
