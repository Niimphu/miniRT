/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:20:11 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/25 14:20:45 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "xyz.h"
#include "shape.h"
#include "draw.h"
#define EPSILON 1e-6

t_xyz ray_intersects_cylinder_disk(t_xyz *viewpoint, t_xyz ray, t_cylinder *cl, t_intersect *intersection);

static double	cylinder_closest_t(double discriminant, double *discr_vars)
{
	double t1;
	double t2;

	t1 = (-discr_vars[1] - sqrt(discriminant)) / (2 * discr_vars[0]);
	t2 = (-discr_vars[1] + sqrt(discriminant)) / (2 * discr_vars[0]);
	if (t1 <= t2)
		return (t2);
	else
		return (t1);
}

t_intersect	ray_intersects_cylinder(t_xyz *viewpoint, t_xyz ray, t_cylinder *cl)
{
	t_xyz		local_cl_center;
	t_xyz		local_cl_axis;
	t_xyz		local_viewpoint;
	t_xyz		local_ray;
	t_matrix	rotation;
	t_intersect	intersection;
	double		discr_vars[3];
	double		discriminant;
	
	intersection = new_intersect();
	rotation = create_rotation_matrix(v_normalize(v_cross(*cl->axis, (t_xyz){0,1,0})), angle_between(v_normalize(*cl->axis),(t_xyz){0,1,0}));
	local_cl_center = v_matrix_mul(rotation, *cl->centre);
	local_cl_axis = v_matrix_mul(rotation, v_normalize(*cl->axis));
	local_viewpoint = v_matrix_mul(rotation, *viewpoint);
	local_ray = v_matrix_mul(rotation, ray);
	discr_vars[0] = v_dot(local_ray, local_ray) - pow(v_dot(local_ray, local_cl_axis), 2);
	discr_vars[1] = 2 * (v_dot(local_cl_center, local_ray) - v_dot(local_ray, local_cl_axis) * v_dot(local_cl_center, local_cl_axis));
	discr_vars[2] = v_dot(local_cl_center, local_cl_center) - pow(v_dot(local_cl_center, local_cl_axis), 2) - pow(cl->diameter / 2, 2);
	discriminant = discr_vars[1] * discr_vars[1] - 4 * discr_vars[0] * discr_vars[2];
	if (discriminant <= 0)
		return (intersection);
	intersection.distance = cylinder_closest_t(discriminant, discr_vars);
	intersection.point = v_add(local_viewpoint, v_scale(local_ray, intersection.distance));
	if (intersection.point.y < cl->centre->y - (cl->height / 2)
		|| intersection.point.y > cl->centre->y + (cl->height / 2))
	{
		rotation = create_rotation_matrix(v_normalize(v_cross((t_xyz){0,1,0},v_normalize(*cl->axis))), -angle_between((t_xyz){0,1,0}, v_normalize(*cl->axis)));
		intersection.point = v_matrix_mul(rotation, ray_intersects_cylinder_disk(viewpoint, ray, cl, &intersection));;
		return (intersection);
	}
	else
	{
		rotation = create_rotation_matrix(v_normalize(v_cross((t_xyz){0,1,0}, v_normalize(*cl->axis))), -angle_between((t_xyz){0,1,0}, v_normalize(*cl->axis)));
		intersection.point = v_matrix_mul(rotation, intersection.point);
		intersection.valid = true;
	}
	intersection.shape = cl;
	intersection.type = CYLINDER;
	intersection.colour = cl->colour;
	return (intersection);
}

int	cylinder_colour(t_cylinder *cl, t_xyz point, t_scene *scene)
{
	double	diffuse_intensity;
	t_rgb	colour;
	t_xyz	light_direction;
	t_xyz	surface_normal;

	surface_normal = v_normalize(v_subtract(point, *cl->centre));
	light_direction = v_normalize(v_subtract(*scene->light->point,
				point));
	diffuse_intensity = fmax(0, fmin(1, (light_direction.x * surface_normal.x
					+ light_direction.y * surface_normal.y
					+ light_direction.z * surface_normal.z)));
	colour = rgb_scale(cl->colour, diffuse_intensity);
	colour = rgb_add(colour, rgb_scale(scene->ambience->colour,
				scene->ambience->lighting));
	return (rgb_to_hex(colour));
}

// Function to calculate the intersection of a ray with the disk of a cylinder
t_xyz ray_intersects_cylinder_disk(t_xyz *viewpoint, t_xyz ray, t_cylinder *cl, t_intersect *intersection)
{

	double distance_to_disk = (cl->height / 2.0) / fabs(ray.y); // is this line causing the disk to float? 
	if (distance_to_disk >= EPSILON)
	{
		// Calculate the intersection point on the disk
		t_xyz intersection_point = v_add(*viewpoint, v_scale(ray, distance_to_disk));
		// Check if the intersection point is within the disk's radius
		if (pow(intersection_point.x - cl->centre->x, 2) + pow(intersection_point.z - cl->centre->z, 2) <= pow(cl->diameter / 2, 2))
		{
			// Update the intersection information
			intersection->distance = distance_to_disk;
			intersection->shape = cl;
			intersection->type = CYLINDER;
			intersection->colour = cl->colour;
			intersection->valid = true;
			return (intersection_point);
		}
	}
	intersection->valid = false;
	return (intersection->point);
}
