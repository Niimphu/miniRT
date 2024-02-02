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

#include "../printer/printer.h"

double	cyl_local_intersect(t_xyz local_viewpoint, t_xyz local_ray, t_cylinder *cl)
{
	double	t1;
	double	t2;
	double	discr_vars[4];

	//printf("local_viewpoint is %f %f %f", local_viewpoint.x, local_viewpoint.y, local_viewpoint.z);
	discr_vars[0] = v_dot(local_ray, local_ray) - pow(v_dot(local_ray, (t_xyz){0, 1, 0}), 2);
	discr_vars[1] = 2 * (v_dot(local_viewpoint, local_ray) - v_dot(local_ray, (t_xyz){0, 1, 0}) * v_dot(local_viewpoint, (t_xyz){0, 1, 0}));
	discr_vars[2] = v_dot(local_viewpoint, local_viewpoint) - pow(v_dot(local_viewpoint, (t_xyz){0, 1, 0}), 2) - pow(cl->radius / 2, 2);
	discr_vars[3] = discr_vars[1] * discr_vars[1] - 4 * discr_vars[0] * discr_vars[2];
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
	t_xyz		local_axis;
	t_xyz		local_viewpoint;
	t_xyz		local_ray;
	t_intersect	intersection;
	double rotation_angle;

	intersection = new_intersect();
	rotation_angle = angle_between(v_normalize(*cl->axis),(t_xyz){0,1,0});
	rotation = create_rotation_matrix(v_cross(*cl->axis, (t_xyz){0,1,0}), rotation_angle);
	to_local = local_matrix(*cl->axis, *cl->centre, rotation_angle);
	to_world = world_matrix(*cl->axis, *cl->centre, rotation_angle);
	//printf("ray is %f %f %f\n", ray.x, ray.y, ray.z);
	local_ray = v_matrix_mul(rotation,ray);
	//printf("local_ray is %f %f %f\n", local_ray.x, local_ray.y, local_ray.z);
	local_viewpoint = v_matrix_mul(to_local, *viewpoint);
	//printf("viewpoint is %f %f %f\n", local_viewpoint.x, local_viewpoint.y, local_viewpoint.z);
	local_axis = v_matrix_mul(rotation, *cl->axis);
	//printf("local axis = %f %f %f \n", local_axis.x,  local_axis.y, local_axis.z);
	intersection.distance = cyl_local_intersect(local_viewpoint, local_ray, cl);
	//printf("intersection distance = %f\n", intersection.distance);
	if (intersection.distance < 0)
		return (intersection);
	intersection.point = v_add(local_viewpoint ,v_scale(local_ray, intersection.distance));
	if (intersection.point.y < cl->centre->y + (cl->height / 2)
		&& intersection.point.y > cl->centre->y - (cl->height / 2))
	{
		intersection.point = v_matrix_mul(to_world, intersection.point);
		//printf("intersection.point = x = %f y = %f z = %f\n",intersection.point.x,intersection.point.y,intersection.point.z);
		intersection.valid = true;
	}
	else
	{
		intersection.point = ray_intersects_cylinder_disk(local_viewpoint, local_ray, intersection, cl);
		intersection.point = v_matrix_mul(to_world, intersection.point);
	}
	intersection.shape = cl;
	intersection.type = CYLINDER;
	intersection.colour = cl->colour;
	return (intersection);
}

/* int	cylinder_colour(t_cylinder *cl, t_xyz point, t_scene *scene)
{
	double	diffuse_intensity;
	t_rgb	colour;
	t_xyz	light_direction;
	t_xyz	surface_normal;

	surface_normal = v_normalize(v_subtract(point, *cl->centre));
	light_direction = v_normalize(v_subtract(*scene->lights->point,
				point));
	diffuse_intensity = fmax(0, fmin(1, (light_direction.x * surface_normal.x
					+ light_direction.y * surface_normal.y
					+ light_direction.z * surface_normal.z)));
	colour = rgb_scale(cl->colour, diffuse_intensity);
	colour = rgb_add(colour, rgb_scale(scene->ambience->colour,
				scene->ambience->lighting));
	return (rgb_to_hex(colour));
} */
