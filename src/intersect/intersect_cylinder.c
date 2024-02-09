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
#include "transform.h"

double	cyl_local_intersect(t_xyz local_viewpoint, t_xyz local_ray, t_cylinder *cl)
{
	double	t1;
	double	t2;
	double	discr_vars[3];
	double	discriminant;

	discr_vars[A] = v_dot(local_ray, local_ray) - pow(v_dot(local_ray, (t_xyz){0, 1, 0}), 2);
	discr_vars[B] = 2 * (v_dot(local_viewpoint, local_ray) - v_dot(local_ray, (t_xyz){0, 1, 0}) * v_dot(local_viewpoint, (t_xyz){0, 1, 0}));
	discr_vars[C] = v_dot(local_viewpoint, local_viewpoint) - pow(v_dot(local_viewpoint, (t_xyz){0, 1, 0}), 2) - pow(cl->radius, 2);
	discriminant = discr_vars[B] * discr_vars[B] - 4 * discr_vars[A] * discr_vars[C];
	if (discriminant < 0)
		return (-1);
	if (discriminant < TOLERANCE)
		return (-discr_vars[B] / 2.0 * discr_vars[A]);
	t1 = (-discr_vars[1] - sqrt(discriminant)) / (2 * discr_vars[0]);
	t2 = (-discr_vars[1] + sqrt(discriminant)) / (2 * discr_vars[0]);
	if (t1 < TOLERANCE && t2 < TOLERANCE)
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

//t_intersect	ray_intersects_caps(t_cylinder *cylinder, t_xyz viewpoint, t_xyz local_viewpoint, t_xyz local_ray)
//{
//	t_intersect	intersection;
//	t_xyz top_centre = (t_xyz) {0, cylinder->height / 2.0, 0};
//	t_xyz bot_centre = (t_xyz) {0, cylinder->height / -2.0, 0};
//	double dist_top =
//			v_dot(v_subtract(top_centre, local_viewpoint), (t_xyz){0, 1, 0}) / v_dot(local_ray, (t_xyz) {0, 1, 0});
//	double dist_bot =
//			v_dot(v_subtract(bot_centre, local_viewpoint), (t_xyz){0, 1, 0}) / v_dot(local_ray, (t_xyz) {0, 1, 0});
//	t_xyz top_point = v_add(local_viewpoint, v_scale(local_ray, dist_top));
//	t_xyz bot_point = v_add(local_viewpoint, v_scale(local_ray, dist_bot));
//	if (p2p_distance(top_centre, top_point) <= cylinder->radius && dist_top > TOLERANCE)
//	{
//		intersection.distance = p2p_distance(local_viewpoint, top_point);
//		intersection.point = v_add(viewpoint, v_scale(local_ray, intersection.distance));
//		if (intersection.distance > TOLERANCE)
//			intersection.valid = true;
//	}
//	else if (p2p_distance(bot_centre, bot_point) <= cylinder->radius && dist_bot > TOLERANCE)
//	{
//		intersection.distance = p2p_distance(local_viewpoint, bot_point);
//		intersection.point = v_add(viewpoint, v_scale(local_ray, intersection.distance));
//		if (intersection.distance > TOLERANCE)
//			intersection.valid = true;
//	}
//	return (intersection);
//}

t_intersect	ray_intersects_cylinder(t_xyz *viewpoint, t_xyz ray, t_cylinder *cl)
{
	t_location_transformation_information_station	t;
	t_intersect										intersection;

	intersection = new_intersect();
	t = new_transform(*cl->axis, *cl->centre, ray, *viewpoint);
	intersection.distance = cyl_local_intersect(t.local_viewpoint, t.local_ray, cl);
	if (intersection.distance < TOLERANCE)
		return (intersection);
	intersection.point = v_add(t.local_viewpoint, v_scale(t.local_ray, intersection.distance));
	if (intersection.point.y < cl->height / 2 && intersection.point.y > cl->height / -2)
	{
		intersection.point = v_add(*viewpoint, v_scale(ray, intersection.distance - TOLERANCE));
		intersection.valid = true;
	}
	else
	{
//		intersection = ray_intersects_caps(cl, *viewpoint, local_viewpoint, local_ray);

		int			closest;
		t_xyz		centre[2];
		centre[TOP] = (t_xyz){0, cl->height / 2.0, 0};
		centre[BOT] = (t_xyz){0, cl->height / -2.0, 0};
		if (p2p_distance(t.local_viewpoint, centre[TOP]) < p2p_distance(t.local_viewpoint, centre[BOT]))
			closest = TOP;
		else
			closest = BOT;

		t_intersect	intersect[2];
		intersect[TOP] = new_intersect();
		intersect[BOT] = new_intersect();

		double		dist[2];
		dist[TOP] = v_dot(v_subtract(centre[TOP], t.local_viewpoint), (t_xyz){0, 1, 0}) / v_dot(t.local_ray, (t_xyz){0, 1, 0});
		dist[BOT] = v_dot(v_subtract(centre[BOT], t.local_viewpoint), (t_xyz){0, 1, 0}) / v_dot(t.local_ray, (t_xyz){0, 1, 0});
		intersect[TOP].point = v_add(t.local_viewpoint, v_scale(t.local_ray, dist[TOP]));
		intersect[BOT].point = v_add(t.local_viewpoint, v_scale(t.local_ray, dist[BOT]));
		if (p2p_distance(centre[TOP], intersect[TOP].point) + TOLERANCE < cl->radius && dist[TOP] > TOLERANCE)
		{
			intersect[TOP].distance = p2p_distance(t.local_viewpoint, intersect[TOP].point);
			intersect[TOP].point = v_add(*viewpoint, v_scale(ray, intersect[TOP].distance));
			if (intersect[TOP].distance > TOLERANCE)
				intersect[TOP].valid = true;
		}
		if (p2p_distance(centre[BOT], intersect[BOT].point) + TOLERANCE < cl->radius && dist[BOT] > TOLERANCE)
		{
			intersect[BOT].distance = p2p_distance(t.local_viewpoint, intersect[BOT].point);
			intersect[BOT].point = v_add(*viewpoint, v_scale(ray, intersect[BOT].distance));
			if (intersect[BOT].distance > TOLERANCE)
				intersect[BOT].valid = true;
		}

		if (intersect[TOP].valid && intersect[BOT].valid)
			intersection = intersect[closest];
		else if (intersect[TOP].valid)
			intersection = intersect[TOP];
		else
			intersection = intersect[BOT];
	}
	intersection.shape = cl;
	intersection.type = CYLINDER;
	intersection.colour = cl->colour;
	return (intersection);
}
