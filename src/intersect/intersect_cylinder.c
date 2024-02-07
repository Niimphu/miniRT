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

#define TOP 0
#define BOT 1

#include "../raytrace/draw.h"
#include "../maths/matrix.h"

double	cyl_local_intersect(t_xyz local_viewpoint, t_xyz local_ray, t_cylinder *cl)
{
	double	t1;
	double	t2;
	double	discr_vars[3];
	double	discriminant;

	discr_vars[0] = v_dot(local_ray, local_ray) - pow(v_dot(local_ray, (t_xyz){0, 1, 0}), 2);
	discr_vars[1] = 2 * (v_dot(local_viewpoint, local_ray) - v_dot(local_ray, (t_xyz){0, 1, 0}) * v_dot(local_viewpoint, (t_xyz){0, 1, 0}));
	discr_vars[2] = v_dot(local_viewpoint, local_viewpoint) - pow(v_dot(local_viewpoint, (t_xyz){0, 1, 0}), 2) - pow(cl->radius, 2);
	discriminant = discr_vars[1] * discr_vars[1] - 4 * discr_vars[0] * discr_vars[2];
	if (discriminant <= 0)
		return (-1);
	t1 = (-discr_vars[1] - sqrt(discriminant)) / (2 * discr_vars[0]);
	t2 = (-discr_vars[1] + sqrt(discriminant)) / (2 * discr_vars[0]);
	if (fabs(t1) < TOLERANCE && fabs(t2) < TOLERANCE)
		return (-1);
	if (t1 < TOLERANCE)
		return (t2);
	if (t2 < TOLERANCE)
		return (t1);
	if (t1 < t2)
		return (t1);
	else
		return (t2);
}

//t_intersect	ray_intersects_caps(t_cylinder *cylinder, t_xyz viewpoint, t_xyz ray)
//{
//	t_intersect	intersect;
//	t_xyz		centre[2];
//	int			closest;
//	double		centre_distance;
//
//	intersect = new_intersect();
//	centre[TOP] = (t_xyz) {0, cylinder->height / 2.0, 0};
//	centre[BOT] = (t_xyz) {0, cylinder->height / -2.0, 0};
//	if (p2p_distance(centre[TOP], viewpoint) < p2p_distance(centre[BOT], viewpoint))
//		closest = TOP;
//	else
//		closest = BOT;
//	centre_distance = v_dot(v_subtract(centre[closest], viewpoint), (t_xyz){0, 1, 0}) / v_dot(ray, (t_xyz) {0, 1, 0});
//	intersect.point = v_add(viewpoint, v_scale(ray, centre_distance));
//	if (p2p_distance(centre[closest], intersect.point) <= cylinder->radius && centre_distance > TOLERANCE)
//	{
//		intersect.distance = p2p_distance(viewpoint, intersect.point);
//		intersect.point = v_add(viewpoint, v_scale(ray, intersect.distance));
//		if (intersect.distance > TOLERANCE)
//			intersect.valid = true;
//	}
//}

t_intersect	ray_intersects_cylinder(t_xyz *viewpoint, t_xyz ray, t_cylinder *cl)
{
	t_matrix	to_local;
	t_matrix	rotation;
	t_xyz		local_viewpoint;
	t_xyz		local_ray;
	t_intersect	intersection;
	double		rotation_angle;

	intersection = new_intersect();
	rotation_angle = angle_between(v_normalize(*cl->axis),(t_xyz){0,1,0});
	rotation = create_rotation_matrix(v_cross(*cl->axis, (t_xyz){0,1,0}), rotation_angle);
	to_local = local_matrix(*cl->axis, *cl->centre, rotation_angle);
	local_ray = v_matrix_mul(rotation, ray);
	local_viewpoint = v_matrix_mul(to_local, *viewpoint);
	intersection.distance = cyl_local_intersect(local_viewpoint, local_ray, cl);
	if (intersection.distance < TOLERANCE)
		return (intersection);
	intersection.point = v_add(local_viewpoint, v_scale(local_ray, intersection.distance));
	if (intersection.point.y < cl->height / 2 && intersection.point.y > cl->height / -2)
	{
		intersection.point = v_add(*viewpoint, v_scale(ray, intersection.distance - TOLERANCE));
		intersection.valid = true;
	}
	else
	{
//		intersection = ray_intersects_caps(cl, local_viewpoint, local_ray);
//		intersection.point = v_add(*viewpoint, v_scale(ray, intersection.distance));
		t_xyz top_centre = (t_xyz) {0, cl->height / 2.0, 0};
		t_xyz bot_centre = (t_xyz) {0, cl->height / -2.0, 0};
		double dist_top =
				v_dot(v_subtract(top_centre, local_viewpoint), (t_xyz){0, 1, 0}) / v_dot(local_ray, (t_xyz) {0, 1, 0});
		double dist_bot =
				v_dot(v_subtract(bot_centre, local_viewpoint), (t_xyz){0, 1, 0}) / v_dot(local_ray, (t_xyz) {0, 1, 0});
		t_xyz top_point = v_add(local_viewpoint, v_scale(local_ray, dist_top));
		t_xyz bot_point = v_add(local_viewpoint, v_scale(local_ray, dist_bot));
		if (p2p_distance(top_centre, top_point) <= cl->radius && dist_top > TOLERANCE)
		{
			intersection.distance = p2p_distance(local_viewpoint, top_point);
			intersection.point = v_add(*viewpoint, v_scale(ray, intersection.distance));
			if (intersection.distance > TOLERANCE)
				intersection.valid = true;
		}
		if (p2p_distance(bot_centre, bot_point) <= cl->radius && dist_bot > TOLERANCE)
		{
			intersection.distance = p2p_distance(local_viewpoint, bot_point);
			intersection.point = v_add(*viewpoint, v_scale(ray, intersection.distance));
			if (intersection.distance > TOLERANCE)
				intersection.valid = true;
		}
	}
	intersection.shape = cl;
	intersection.type = CYLINDER;
	intersection.colour = cl->colour;
	return (intersection);
}
