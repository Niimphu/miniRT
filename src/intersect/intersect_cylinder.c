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
//	printf("xz plane intersection: ");
//	t_xyz	plane_intersection;
//	plane_intersection = v_add(v_scale(local_ray, v_length(local_viewpoint)), local_viewpoint);
//	print_coord_info(&plane_intersection);
	intersect = local_intersection(local_viewpoint, local_ray,
			cylinder);
	intersect.point = v_add(*cylinder->centre, m_v_multiply(reverse, intersect.point));
	intersect = local_intersection(*viewpoint, ray, cylinder);
	return (intersect);
}

t_intersect	local_intersection(t_xyz viewpoint, t_xyz ray,
				t_cylinder *cylinder)
{
//	t_intersect	intersect;
//	double		discriminant;
//	double		discr_vars[3];
//
//	intersect = new_intersect();
//	discr_vars[A] = ray.x * ray.x + ray.z * ray.z;
//	discr_vars[B] = 2 * (viewpoint.x * ray.x + viewpoint.z * ray.z);
//	discr_vars[C] = viewpoint.x * viewpoint.x + viewpoint.z * viewpoint.z;
//	discriminant = pow(discr_vars[B], 2) - 4 * discr_vars[A] * discr_vars[C];
//	if (discriminant < 0)
//		return (intersect);
//	intersect.distance = intersection_distance(discriminant, discr_vars);
//	if (intersect.distance < TOLERANCE)
//		return (intersect);
//	intersect.point = v_add(viewpoint, v_scale(ray, intersect.distance));
//	return ((t_intersect){true, intersect.point,
//		cylinder->colour, intersect.distance, cylinder,
//		CYLINDER, cylinder->material});



//	t_intersect	intersection;
//	double		discr_vars[3];
//	double		discriminant;
//
//	intersection = new_intersect();
//	discr_vars[A] = ray.x * ray.x + ray.z * ray.z;
//	discr_vars[B] = 2 * (viewpoint.x * ray.x + viewpoint.z * ray.z);
//	discr_vars[C] = viewpoint.x * viewpoint.x + viewpoint.z * viewpoint.z;
//	discriminant = pow(discr_vars[B], 2) - 4 * discr_vars[A] * discr_vars[C];
//	if (discriminant < 0)
//		return (intersection);
//	printf("%f\n", discriminant);
//	intersection.distance = intersection_distance(discriminant, discr_vars);
//	if (intersection.distance < TOLERANCE)
//		return (intersection);
//	intersection.point = v_add(viewpoint, v_scale(ray, intersection.distance));
//	if (intersection.point.y <= cylinder->centre->y + (cylinder->height / 2)
//		&& intersection.point.y >= cylinder->centre->y - (cylinder->height / 2))
//	{
///* 		rotation = create_rotation_matrix(v_normalize(v_cross((t_xyz){0,1,0},v_normalize(*cl->axis))), -angle_between((t_xyz){0,1,0}, v_normalize(*cl->axis)));
//		intersection.point = v_matrix_mul(rotation, ray_intersects_cylinder_disk(&local_viewpoint, local_ray, cl, &intersection, local_cl_center));
//		return (intersection);
//	}
//	else
//	{ */
//		intersection.valid = true;
//	}
//	intersection.shape = cylinder;
//	intersection.type = CYLINDER;
//	intersection.colour = cylinder->colour;

//	t_intersect	intersect;
//
//	double		r = cylinder->diameter / 2;
//
////	t_xyz		top = (t_xyz){0, cylinder->height / 2, 0};
//	t_xyz		bottom = (t_xyz){0, cylinder->height / -2, 0};
//
//	t_xyz		axis = (t_xyz){0, 1, 0};
//	t_xyz		to_cam = v_subtract(viewpoint, bottom);
//
//	double		axis2 = v_dot(axis, axis);
//	double		axisray = v_dot(axis, ray);
//	double		camaxis = v_dot(to_cam, axis);
//
//	double		k2 = axis2 - (axisray * axisray);
//	double		k1 = axis2 * v_dot(to_cam, ray) - (camaxis - axisray);
//	double		k0 = axis2 * v_dot(to_cam, to_cam) - (camaxis * camaxis) - r * r * axis2;
//	double		h = k1 * k1 - k2 * k0;
//
//	h = sqrt(h);
//
//	double		t = (-k1 - h) / k2;
//
//	double		y = camaxis + t * axisray;
//
//	if (y < 0.0 || y > axis2)
//		return (new_intersect());
//
//	intersect.distance = t;
//	intersect.point = v_scale(v_subtract(v_add(to_cam, v_scale(ray, t)), v_scale(v_scale(axis, y), 1 / axis2)), 1 / r);


//	t_intersect	intersect = new_intersect();
//	double		radius = cylinder->diameter / 2;
//
//	t_xyz		cy_to_cam = v_subtract(viewpoint, *cylinder->centre);
//	double		axisray = v_dot(*cylinder->axis, ray);
//	double		axis_tocam = v_dot(*cylinder->axis, cy_to_cam);
//
//	double		a = 1.0 - axisray * axisray;
//	double		b = v_dot(cy_to_cam, ray) - axis_tocam * axisray;
//	double		c = v_dot(cy_to_cam, cy_to_cam) - axis_tocam * axis_tocam - radius * radius;
//
//	double		h = b * b - a * c;
//	if (h < 0.0)
//		return (intersect);
//
//	h = sqrt(h);


	t_intersect	intersect;
	double		discr_vars[3];
	double		discriminant;

	intersect = new_intersect();

	t_xyz		u;
	t_xyz		v;

	u = v_scale(*cylinder->axis, v_dot(ray, *cylinder->axis));
	u = v_subtract(v_subtract(viewpoint, *cylinder->centre), u);

	v = v_scale(*cylinder->axis, v_dot(ray, *cylinder->axis));
	v = v_subtract(ray, v);

	discr_vars[A] = v_dot(v, v);
	discr_vars[B] = 2 * v_dot(v, u);
	discr_vars[C] = v_dot(u, u) - cylinder->radius * cylinder->radius;

	discriminant = pow(discr_vars[B], 2) - 4 * discr_vars[A] * discr_vars[C];
	printf("%f!!\n", discriminant);
	if (discriminant < 0)
		return (intersect);
	intersect.distance = intersection_distance(discriminant, discr_vars);


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
