/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:31:46 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/13 16:56:17 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include "miniRT.h"
# include "xyz.h"
# include "transform.h"

typedef struct s_intersect
{
	bool		valid;
	t_xyz		point;
	t_rgb		colour;
	double		distance;
	void		*shape;
	int			type;
	t_material	material;
}				t_intersect;

t_intersect	new_intersect(void);

t_intersect	ray_intersects_sphere(t_xyz *viewpoint, t_xyz ray,
				t_sphere *sphere);
t_intersect	ray_intersects_plane(t_xyz *viewpoint, t_xyz ray, t_plane *plane);
t_intersect	ray_intersects_cylinder(t_xyz *viewpoint, t_xyz ray,
				t_cylinder *cylinder);
t_intersect	ray_intersects_cone(t_xyz *viewpoint, t_xyz ray,
				t_cone *co);
t_intersect	ray_intersects_triangle(t_xyz *viewpoint,
				t_xyz ray, t_triangle *triangle);

bool		intersects_any_sphere(t_xyz intersect_point, t_xyz light_xyz,
				t_list *spheres, t_xyz to_light);
bool		intersects_any_plane(t_xyz intersect_point, t_xyz light_xyz,
				t_list *planes, t_xyz to_light);
bool		intersects_any_cylinder(t_xyz intersect_point, t_xyz light_xyz,
				t_list *cylinders, t_xyz to_light);
bool		intersects_any_cone(t_xyz intersect_point, t_xyz light_xyz,
				t_list *cones, t_xyz to_light);
bool		intersects_any_triangle(t_xyz intersect_point, t_xyz light_xyz,
				t_list *triangles, t_xyz to_light);

t_intersect	get_closest_cone(t_xyz viewpoint, t_xyz ray, t_list *cones);
t_intersect	get_closest_triangle(t_xyz viewpoint, t_xyz ray,
				t_list *triangles);

t_intersect	closest_side(t_xyz distances, t_cylinder *cylinder,
				t_location_transformation_information_station t);

#endif
