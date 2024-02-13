/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:31:46 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/13 16:27:06 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include "miniRT.h"
# include "xyz.h"

typedef struct s_intersect
{
	bool		valid;
	t_xyz		point;
	t_xyz		point_normal;
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

bool		intersects_sphere(t_xyz intersect_point, t_xyz light_xyz,
				t_list *spheres, t_xyz to_light);
bool		intersects_plane(t_xyz intersect_point, t_xyz light_xyz,
				t_list *planes, t_xyz to_light);
bool		intersects_cylinder(t_xyz intersect_point, t_xyz light_xyz,
				t_list *cylinders, t_xyz to_light);
bool		intersects_cone(t_xyz intersect_point, t_xyz light_xyz,
				t_list *cones, t_xyz to_light);
bool		intersects_triangle(t_xyz intersect_point, t_xyz light_xyz,
				t_list *triangles, t_xyz to_light);
#endif
