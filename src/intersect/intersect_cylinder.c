/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:08:30 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/28 20:23:24 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define A 0
#define B 1
#define C 2

#include "../raytrace/draw.h"
#include "../maths/matrix.h"

#include "../printer/printer.h"

t_intersect		local_intersection(t_xyz viewpoint, t_xyz ray,
					t_cylinder *cylinder);
static double	intersection_distance(double discriminant, double *vars);
t_xyz			localise_viewpoint(t_xyz viewpoint, t_xyz cy_centre,
					t_matrix rotation);

t_intersect	ray_intersects_cylinder(t_xyz *viewpoint, t_xyz ray,
					t_cylinder *cylinder)
{
	t_matrix	rotation;
	t_matrix	reverse;
	t_intersect	intersect;
	t_xyz		local_viewpoint;
	t_xyz		local_ray;

	rotation = create_rotation_matrix(identity_matrix(),
			v_normalize(v_cross(*cylinder->axis, (t_xyz){0, 1, 0})),
			v_angle(v_normalize(*cylinder->axis), (t_xyz){0, 1, 0}));
	reverse = create_rotation_matrix(identity_matrix(),
			v_normalize(v_cross(*cylinder->axis, (t_xyz){0, 1, 0})),
			v_angle((t_xyz){0, 1, 0}, v_normalize(*cylinder->axis)));
	local_viewpoint = localise_viewpoint(*viewpoint, *cylinder->centre,
			rotation);
	local_ray = m_v_multiply(rotation, ray);
	intersect = local_intersection(local_viewpoint, local_ray,
			cylinder);
	intersect.point = v_add(*cylinder->centre, m_v_multiply(reverse, intersect.point));
	return (intersect);
}

t_intersect	local_intersection(t_xyz viewpoint, t_xyz ray,
				t_cylinder *cylinder)
{
	t_intersect	intersect;
	double		discriminant;
	double		discr_vars[3];

	intersect = new_intersect();
	discr_vars[A] = ray.x * ray.x + ray.z * ray.z;
	discr_vars[B] = 2 * (viewpoint.x * ray.x + viewpoint.z * ray.z);
	discr_vars[C] = viewpoint.x * viewpoint.x + viewpoint.z * viewpoint.z;
	discriminant = pow(discr_vars[B], 2) - 4 * discr_vars[A] * discr_vars[C];
	if (discriminant < 0)
		return (intersect);
	intersect.distance = intersection_distance(discriminant, discr_vars);
	if (fabs(intersect.distance) < TOLERANCE)
		return (intersect);
	intersect.point = v_add(viewpoint, v_scale(ray, intersect.distance));
	return ((t_intersect){true, intersect.point,
		cylinder->colour, intersect.distance, cylinder,
		CYLINDER, cylinder->material});
}

t_xyz	localise_viewpoint(t_xyz viewpoint, t_xyz cy_centre, t_matrix rotation)
{
	t_xyz	local_viewpoint;
	t_xyz	cy_to_cam;
	t_xyz	cy_to_local_cam;

	cy_to_cam = v_subtract(viewpoint, cy_centre);
	cy_to_local_cam = m_v_multiply(rotation, cy_to_cam);
	local_viewpoint = v_add(cy_centre, cy_to_local_cam);
	local_viewpoint = v_subtract(local_viewpoint, cy_centre);
	return (local_viewpoint);
}

static double	intersection_distance(double discriminant, double *vars)
{
	double	x1;
	double	x2;

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
