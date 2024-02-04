/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:20:11 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/01 20:39:09 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "matrix.h"
#include "xyz.h"
#include "draw.h"
#include "printer.h"
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
	t_xyz		local_viewpoint;
	t_xyz		local_ray;
	t_intersect	intersection;
	double rotation_angle;

	intersection = new_intersect();
	rotation_angle = angle_between(v_normalize(*cl->axis),(t_xyz){0,1,0});
	rotation = create_rotation_matrix(v_cross(*cl->axis, (t_xyz){0,1,0}), rotation_angle);
	to_local = local_matrix(*cl->axis, *cl->centre, rotation_angle);
	to_world = world_matrix(*cl->axis, *cl->centre, rotation_angle);
	local_ray = v_matrix_mul(rotation,ray);
	local_viewpoint = v_matrix_mul(to_local, *viewpoint);
	intersection.distance = cyl_local_intersect(local_viewpoint, local_ray, cl);
	if (intersection.distance < 0)
		return (intersection);
	intersection.point = v_add(local_viewpoint ,v_scale(local_ray, intersection.distance));
	if (intersection.point.y < cl->height / 2 && intersection.point.y > cl->height / -2)
	{
		intersection.point = v_matrix_mul(to_world, intersection.point);
		intersection.valid = true;
	}
	else
	{
		t_xyz	top_centre = (t_xyz){0, cl->height / 2.0, 0};
		t_xyz	bot_centre = (t_xyz){0, cl->height / -2.0, 0};
		double	dist_top = v_dot(v_subtract(top_centre, local_viewpoint), (t_xyz){0, 1, 0}) / v_dot(local_ray, (t_xyz){0, 1, 0});
		double	dist_bot = v_dot(v_subtract(bot_centre, local_viewpoint), (t_xyz){0, 1, 0}) / v_dot(local_ray, (t_xyz){0, 1, 0});
		t_xyz	top_point = v_add(local_viewpoint, v_scale(local_ray, dist_top));
		t_xyz	bot_point = v_add(local_viewpoint, v_scale(local_ray, dist_bot));
		if (p2p_distance(top_centre, top_point) <= cl->diameter / 2)
		{
			intersection.point = v_matrix_mul(to_world, top_point);
			intersection.distance = p2p_distance(*viewpoint, intersection.point);
			intersection.valid = true;
		}
		if (p2p_distance(bot_centre, bot_point) <= cl->diameter / 2)
		{
			intersection.point = v_matrix_mul(to_world, bot_point);
			intersection.distance = p2p_distance(*viewpoint, intersection.point);
			intersection.valid = true;
		}
	}
//	{
//		t_xyz top_centre = (t_xyz) {cl->centre->x, cl->height / 2, cl->centre->z};
//		t_xyz bot_centre = (t_xyz) {cl->centre->x, -cl->height / 2, cl->centre->z};
//		t_xyz top_axis = (t_xyz) {0, 1, 0};
//		t_xyz bot_axis = (t_xyz) {0, -1, 0};
//		double top_dot = v_dot(top_axis, local_ray);
//		double bot_dot = v_dot(bot_axis, local_ray);
//		t_intersect top_intersect = new_intersect();
//		t_intersect bot_intersect = new_intersect();
//		top_intersect.distance = v_dot(v_subtract(top_centre, local_viewpoint), top_axis) / top_dot;
//		bot_intersect.distance = v_dot(v_subtract(bot_centre, local_viewpoint), bot_axis) / bot_dot;
//		top_intersect.point = v_add(*viewpoint, v_scale(local_ray, top_intersect.distance));
//		bot_intersect.point = v_add(*viewpoint, v_scale(local_ray, bot_intersect.distance));
//		if (p2p_distance(top_centre, top_intersect.point) <= cl->diameter / 2 && top_dot != 0 &&
//			top_intersect.distance >= 0.0) {
//			intersection = top_intersect;
//			intersection.point = v_matrix_mul(to_world, intersection.point);
//			intersection.valid = true;
//		} else if (p2p_distance(bot_centre, bot_intersect.point) <= cl->diameter / 2 && bot_dot != 0 &&
//				   bot_intersect.distance >= 0.0) {
//			intersection = bot_intersect;
//			intersection.point = v_matrix_mul(to_world, intersection.point);
//			intersection.valid = true;
//		}
//	}
	intersection.shape = cl;
	intersection.type = CYLINDER;
	intersection.colour = cl->colour;
	return (intersection);
}

t_xyz	cylinder_normal(t_cylinder *cylinder, t_xyz point)
{
	t_xyz	to_surface;
	double	to_surface_axis_dot;
	double	axis_l2;
	t_xyz	axis_parallel;
	t_xyz	surface_normal;

	to_surface = v_subtract(point, *cylinder->centre);
	to_surface_axis_dot = v_dot(*cylinder->axis, to_surface);
	axis_l2 = v_dot(*cylinder->axis, *cylinder->axis);
	axis_parallel = v_scale(*cylinder->axis, (to_surface_axis_dot / axis_l2));
	surface_normal = v_subtract(to_surface, axis_parallel);
	return (v_normalize(surface_normal));
}

int	cylinder_colour(t_cylinder *cl, t_xyz point, t_scene *scene)
{
	double	diffuse_intensity;
	t_rgb	colour;
	t_xyz	light_direction;
	t_xyz	surface_normal;

	surface_normal = cylinder_normal(cl, point);
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
