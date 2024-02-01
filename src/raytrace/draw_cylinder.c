/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:20:11 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/01 20:28:54 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "xyz.h"
#include "shape.h"
#include "draw.h"
#define EPSILON 1e-6

t_xyz ray_intersects_cylinder_disk(t_xyz *viewpoint, t_xyz ray, t_cylinder *cl, t_intersect *intersection, t_xyz centre);

/* t_xyz	cylinder_closest_t(double discriminant, double *discr_vars, t_xyz viewpoint, t_xyz ray, t_intersect intersection)
{

}
 */

double	cyl_local_intersect(t_xyz local_viewpoint, t_xyz local_ray, t_cylinder *cl)
{
	double	t1;
	double	t2;
	double	discr_vars[4];

	//printf("local_viewpoint is %f %f %f", local_viewpoint.x, local_viewpoint.y, local_viewpoint.z);
	discr_vars[0] = v_dot(local_ray, local_ray) - pow(v_dot(local_ray, (t_xyz){0, 1, 0}), 2);
	discr_vars[1] = 2 * (v_dot(local_viewpoint, local_ray) - v_dot(local_ray, (t_xyz){0, 1, 0}) * v_dot(local_viewpoint, (t_xyz){0, 1, 0}));
	discr_vars[2] = v_dot(local_viewpoint, local_viewpoint) - pow(v_dot(local_viewpoint, (t_xyz){0, 1, 0}), 2) - pow(cl->diameter / 2, 2);
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
/* double	cyl_local_intersect(t_xyz local_viewpoint, t_xyz local_ray, t_cylinder *cl)
{
    double a = local_ray.x * local_ray.x + local_ray.z * local_ray.z;
    double b = 2 * (local_ray.x * local_viewpoint.x + local_ray.z * local_viewpoint.z);
    double c = local_viewpoint.x * local_viewpoint.x + local_viewpoint.z * local_viewpoint.z - (cl->diameter / 2) * (cl->diameter / 2);

    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        return -1.0; // No intersection

    // Calculate the two possible intersection distances
    double t1 = (-b + sqrt(discriminant)) / (2 * a);
    double t2 = (-b - sqrt(discriminant)) / (2 * a);

    // Check if either intersection point is in front of the viewpoint
    if ((t1 > 0 || t2 > 0) && (t1 < 0 || t2 < 0 || t1 < t2)) {
        // Return the minimum positive intersection distance
        return (t1 < 0) ? t2 : t1;
    } else {
        // Both intersections are behind the viewpoint or negative
        return -1.0;
    }
} */

t_xyz	localise_viewpoint(t_xyz viewpoint, t_xyz cy_centre, t_matrix rotation)
{
	t_xyz	local_viewpoint;
	t_xyz	cy_to_cam;
	t_xyz	cy_to_local_cam;

	cy_to_cam = v_subtract(viewpoint, cy_centre);
	cy_to_local_cam = v_matrix_mul(rotation, cy_to_cam);
	local_viewpoint = v_add(cy_centre, cy_to_local_cam);
	local_viewpoint = v_subtract(local_viewpoint, cy_centre);
	return (local_viewpoint);
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
	printf("ray is %f %f %f\n", ray.x, ray.y, ray.z);
	local_ray = v_matrix_mul(rotation,ray);
	printf("local_ray is %f %f %f\n", local_ray.x, local_ray.y, local_ray.z);
	local_viewpoint = v_matrix_mul(to_local, *viewpoint);
	printf("viewpoint is %f %f %f\n", local_viewpoint.x, local_viewpoint.y, local_viewpoint.z);
	local_axis = v_matrix_mul(rotation, *cl->axis);
	printf("local axis = %f %f %f \n", local_axis.x,  local_axis.y, local_axis.z);
	intersection.distance = cyl_local_intersect(local_viewpoint, local_ray, cl);
	printf("intersection distance = %f\n", intersection.distance);
	if (intersection.distance < 0)
		return (intersection);
	intersection.point = v_add(local_viewpoint ,v_scale(local_ray, intersection.distance));
	if (fabs(intersection.point.y) <= fabs(cl->centre->y) + (cl->height / 2))
	{
		intersection.point = v_matrix_mul(to_world, intersection.point);
		//printf("intersection.point = x = %f y = %f z = %f\n",intersection.point.x,intersection.point.y,intersection.point.z);
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

/* t_xyz ray_intersects_cylinder_disk(t_xyz *viewpoint, t_xyz ray, t_cylinder *cl, t_intersect *intersection, t_xyz centre)
{

	return (intersection->point);
} */
