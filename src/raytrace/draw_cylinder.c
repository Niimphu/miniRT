/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:20:11 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/14 17:53:23 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "xyz.h"
#include "shape.h"
#include "draw.h"

static double	cylinder_closest_t(double discriminant, double *discr_vars)
{
	double t1;
	double t2;

	t1 = (-discr_vars[1] - sqrt(discriminant)) / (2 * discr_vars[0]);
	t2 = (-discr_vars[1] + sqrt(discriminant)) / (2 * discr_vars[0]);
	if (t1 <= t2)
		return (t1);
	else
		return (t2);
}

t_intersect	ray_intersects_cylinder(t_xyz *viewpoint, t_xyz ray, t_cylinder *cl)
{
	t_xyz		local_cl_center;
	t_xyz		local_cl_axis;
	t_xyz		local_viewpoint;
	t_xyz		local_ray;
	t_matrix	translation;
	t_matrix	rotation;
	t_intersect	intersection;
	double		discr_vars[3];
	double		discriminant;

	intersection = new_intersect();
	//translate to local coordinates, get local t_xyz viewpoint and ray
	translation = create_4x4_matrix(-cl->centre->x, -cl->centre->x, - cl->centre->z);
	local_viewpoint = v_matrix_mul(translation, viewpoint);
	local_ray = v_matrix_mul(translation, &ray);
	/* to_cl_center = v_subtract(*viewpoint, *cl->centre); */
	//align axis with unit axis,created rotatematrix and multiply cl->center and cl->axis with it
	//transfrom viewpoint and ray with rotation matrix
	rotation = rotation_matrix(*cl->axis, atan2f(0 - cl->axis->x, 0 - cl->axis->z));
	local_cl_center = v_matrix_mul(rotation, cl->centre);
	local_cl_axis = v_matrix_mul(rotation, cl->axis);
	local_viewpoint = v_matrix_mul(translation, &local_viewpoint);
	local_ray = v_matrix_mul(translation, &local_ray);

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
		intersection.valid = false;
		return (intersection);
	}
	else
	{
		t_matrix inv;

		inv = inverse_matrix(translation);
		intersection.point = v_matrix_mul(inv, &intersection.point);
	}
	intersection.shape = cl;
	intersection.type = CYLINDER;
	intersection.colour = cl->colour;
	intersection.valid = true;
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

/* t_intersect *calculate_cylinder_intersection(t_xyz *viewpoint, t_xyz ray, t_cylinder *cylinder)
{
    t_intersect *intersection = (t_intersect *)malloc(sizeof(t_intersect));
    if (!intersection) {
        // Handle memory allocation failure
        return NULL;
    }

    // Define the parameters for the quadratic equation
    t_xyz oc = {viewpoint->x - cylinder->centre->x, viewpoint->y - cylinder->centre->y, viewpoint->z - cylinder->centre->z};
    double a = dot_product(&ray, &ray) - pow(dot_product(&ray, cylinder->axis), 2);
    double b = 2 * (dot_product(&oc, &ray) - dot_product(&ray, cylinder->axis) * dot_product(&oc, cylinder->axis));
    double c = dot_product(&oc, &oc) - pow(dot_product(&oc, cylinder->axis), 2) - pow(cylinder->diameter / 2, 2);

    // Calculate the discriminant
    double discriminant = b * b - 4 * a * c;

    // Check if there is a real intersection
    if (discriminant < 0) {
        free(intersection);
        return NULL;
    }

    // Find the closest intersection point
    double t1 = (-b - sqrt(discriminant)) / (2 * a);
    double t2 = (-b + sqrt(discriminant)) / (2 * a);
    double t = (t1 < t2) ? t1 : t2;

    // Check if the intersection point is within the height of the cylinder
    double intersection_y = viewpoint->y + t * ray.y;
    if (intersection_y < cylinder->centre->y || intersection_y > cylinder->centre->y + cylinder->height) {
        free(intersection);
        return NULL;
    }

    // Calculate the intersection point and normal
    intersection->position.x = ;
    intersection->position.y = intersection_y;
    intersection->position.z = viewpoint->z + t * ray.z;

    t_xyz oc_to_intersection = {intersection->position.x - cylinder->centre->x, intersection->position.y - cylinder->centre->y, intersection->position.z - cylinder->centre->z};
    intersection->normal = oc_to_intersection;
    intersection->color = cylinder->colour;

    return intersection;
} */