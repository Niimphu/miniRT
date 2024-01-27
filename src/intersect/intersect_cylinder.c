/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:08:30 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/27 18:08:30 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define A 0
#define B 1
#define C 2

#include "../raytrace/draw.h"
#include "../maths/matrix.h"

t_intersect		local_intersection(t_xyz viewpoint, t_xyz ray,
					t_cylinder *cylinder, t_xyz axis);
static double	intersection_distance(double discriminant, double *vars);

t_intersect	ray_intersects_cylinder(t_xyz *viewpoint, t_xyz ray,
					t_cylinder *cylinder)
{
	t_matrix	rotation;
	t_intersect	intersect;
	t_xyz		local_axis;
	t_xyz		local_viewpoint;
	t_xyz		local_ray;

	rotation = create_rotation_matrix(identity_matrix(),
			v_normalize(v_cross(*cylinder->axis, (t_xyz){0, 1, 0})),
			v_angle(v_normalize(*cylinder->axis), (t_xyz){0, 1, 0}));
	local_axis = m_v_multiply(rotation, *cylinder->axis);
	local_viewpoint = m_v_multiply(rotation, *viewpoint);
	local_ray = m_v_multiply(rotation, ray);
	intersect = local_intersection(local_viewpoint, local_ray,
			cylinder, local_axis);
	return (intersect);
}

t_intersect	local_intersection(t_xyz viewpoint, t_xyz ray,
				t_cylinder *cylinder, t_xyz axis)
{
	t_intersect	intersect;
	double		discriminant;
	double		discr_vars[3];
	t_xyz		cy_to_cam;

	intersect = new_intersect();
	cy_to_cam = v_normalize(v_subtract(viewpoint, *cylinder->centre));
	discr_vars[A] = v_dot(ray, ray) - pow(v_dot(ray, axis), 2);
	discr_vars[B] = 2 * (v_dot(cy_to_cam, ray) - v_dot(ray, axis)
			* v_dot(viewpoint, axis));
	discr_vars[C] = v_dot(cy_to_cam, cy_to_cam)
		- pow(v_dot(cy_to_cam, axis), 2) - pow(cylinder->diameter / 2, 2);
	discriminant = discr_vars[B] * discr_vars[B]
		- 4 * discr_vars[A] * discr_vars[C];
	if (discriminant < -TOLERANCE)
		return (new_intersect());
	intersect.distance = intersection_distance(discriminant, discr_vars);
	if (intersect.distance < TOLERANCE)
		return (new_intersect());
	return ((t_intersect){true,
		v_add(viewpoint, v_scale(ray, intersect.distance)),
		cylinder->colour, intersect.distance, cylinder,
		SPHERE, cylinder->material});
}

static double	intersection_distance(double discriminant, double *vars)
{
	if (discriminant < TOLERANCE)
		return (vars[B] / 2.0);
	return (fmin(fmax(0, -(vars[B]) - sqrt(discriminant)) / (2.0 * vars[A]),
			fmax(0, -(vars[B]) + sqrt(discriminant)) / (2.0 * vars[A])));
}
