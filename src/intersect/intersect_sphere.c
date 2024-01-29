/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:20:58 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/28 17:56:32 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define A 0
#define B 1
#define C 2

#include "../raytrace/draw.h"

static double	intersection_distance(double discriminant, const double *vars);

t_intersect	ray_intersects_sphere(t_xyz *viewpoint, t_xyz ray, t_sphere *sphere)
{
	t_xyz		to_sphere_centre;
	double		discr_vars[3];
	double		discriminant;
	t_intersect	intersection;

	to_sphere_centre = v_subtract(*viewpoint, *sphere->centre);
	discr_vars[A] = v_dot(ray, ray);
	discr_vars[B] = 2.0 * v_dot(to_sphere_centre, ray);
	discr_vars[C] = v_dot(to_sphere_centre, to_sphere_centre)
		- (pow(sphere->diameter, 2) * 0.25);
	discriminant = pow(discr_vars[B], 2) - 4 * discr_vars[A] * discr_vars[C];
	intersection = new_intersect();
	if (discriminant < 0)
		return (new_intersect());
	intersection.distance = intersection_distance(discriminant, discr_vars);
	if (intersection.distance < TOLERANCE)
		return (intersection);
	return ((t_intersect){true,
		v_add(*viewpoint, v_scale(ray, intersection.distance)),
		sphere->colour, intersection.distance, sphere,
		SPHERE, sphere->material});
}

static double	intersection_distance(double discriminant, const double *vars)
{
	double	x1;
	double	x2;

	if (discriminant < TOLERANCE)
		return ((-vars[B]) / 2.0 * vars[A]);
	x1 = (-(vars[B]) - sqrt(discriminant)) / (2.0 * vars[A]);
	x2 = (-(vars[B]) + sqrt(discriminant)) / (2.0 * vars[A]);
	if (fabs(x1) < TOLERANCE && fabs(x2) < TOLERANCE)
		return (0);
	if (fabs(x1) < TOLERANCE)
		return (x2);
	if (fabs(x2) < TOLERANCE)
		return (x1);
	if (fabs(x1) < fabs(x2))
		return (x1);
	else
		return (x2);
}
