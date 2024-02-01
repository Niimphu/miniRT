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
static double	intersection_distance(double discriminant, const double *vars);
t_xyz			localise_viewpoint(t_xyz viewpoint, t_xyz cy_centre,
					t_matrix rotation);

t_intersect	ray_intersects_cylinder(t_xyz *viewpoint, t_xyz ray,
					t_cylinder *cylinder)
{
//	t_matrix	rotation;
//	t_matrix	reverse;
	t_intersect	intersect;
//	t_xyz		local_viewpoint;
//	t_xyz		local_ray;

//	rotation = create_rotation_matrix(identity_matrix(),
//			v_normalize(v_cross(*cylinder->axis, (t_xyz){0, 1, 0})),
//			v_angle(v_normalize(*cylinder->axis), (t_xyz){0, 1, 0}));
//	reverse = create_rotation_matrix(identity_matrix(),
//			v_normalize(v_cross(*cylinder->axis, (t_xyz){0, 1, 0})),
//			v_angle((t_xyz){0, 1, 0}, v_normalize(*cylinder->axis)));
//	local_viewpoint = localise_viewpoint(*viewpoint, *cylinder->centre,
//			rotation);
//	local_ray = m_v_multiply(rotation, ray);

//	intersect = local_intersection(local_viewpoint, local_ray,
//			cylinder);
//	intersect.point = v_add(*cylinder->centre, m_v_multiply(reverse, intersect.point));

	intersect = local_intersection(*viewpoint, ray, cylinder);
	return (intersect);
}

t_intersect	local_intersection(t_xyz viewpoint, t_xyz ray,
				t_cylinder *cylinder)
{
	t_intersect	intersect;
	t_xyz		local_cl_center;
	t_xyz		local_cl_axis;
	t_xyz		local_viewpoint;
	t_xyz		local_ray;
	t_matrix	rotation;
	double		discr_vars[3];
	double		discriminant;

	intersect = new_intersect();
	rotation = create_rotation_matrix(identity_matrix(), v_normalize(v_cross(*cylinder->axis, (t_xyz){0,1,0})), v_angle(v_normalize(*cylinder->axis),(t_xyz){0,1,0}));
	local_cl_center = m_v_multiply(rotation, *cylinder->centre);
	local_cl_axis = m_v_multiply(rotation, v_normalize(*cylinder->axis));
	local_viewpoint = m_v_multiply(rotation, viewpoint);
	local_ray = m_v_multiply(rotation, ray);
	discr_vars[0] = v_dot(local_ray, local_ray) - pow(v_dot(local_ray, local_cl_axis), 2);
	discr_vars[1] = 2 * (v_dot(local_cl_center, local_ray) - v_dot(local_ray, local_cl_axis) * v_dot(local_cl_center, local_cl_axis));
	discr_vars[2] = v_dot(local_cl_center, local_cl_center) - pow(v_dot(local_cl_center, local_cl_axis), 2) - pow(cylinder->radius, 2);
	discriminant = discr_vars[1] * discr_vars[1] - 4 * discr_vars[0] * discr_vars[2];
	if (discriminant <= 0)
		return (intersect);
	intersect.distance = intersection_distance(discriminant, discr_vars);
	intersect.point = v_add(local_viewpoint, v_scale(local_ray, intersect.distance));
	if (intersect.point.y <= cylinder->centre->y - (cylinder->height / 2)
		|| intersect.point.y >= cylinder->centre->y + (cylinder->height / 2))
	{
		//disc
		return (intersect);
	}
	else
	{
		rotation = create_rotation_matrix(identity_matrix(), v_normalize(v_cross((t_xyz){0,1,0}, v_normalize(*cylinder->axis))), -v_angle((t_xyz){0,1,0}, v_normalize(*cylinder->axis)));
		intersect.point = m_v_multiply(rotation, intersect.point);
		intersect.valid = true;
	}
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
