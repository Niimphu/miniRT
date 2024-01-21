/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 20:20:58 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/19 20:20:58 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define A 0
#define B 1
#define C 2

#include "miniRT.h"
#include "xyz.h"
#include "draw.h"

t_intersect	ray_interects_sphere(t_xyz *viewpoint, t_xyz ray, t_sphere *sphere)
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
	intersection.distance = (-(discr_vars[B]) - sqrt(discriminant))
		/ (2.0 * discr_vars[A]);
	if (fabs(intersection.distance) < TOLERANCE)
		intersection.distance = (-(discr_vars[B]) + sqrt(discriminant))
			/ (2.0 * discr_vars[A]);
	else if (intersection.distance < 0)
		return (intersection);
	return ((t_intersect){true,
		v_add(*viewpoint, v_scale(ray, intersection.distance)),
		sphere->colour, intersection.distance, sphere,
		SPHERE, sphere->material});
}
