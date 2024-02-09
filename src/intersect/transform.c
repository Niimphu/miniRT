/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 23:47:11 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/08 23:47:11 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transform.h"

t_location_transformation_information_station	new_transform(t_xyz axis,
				t_xyz shape_centre, t_xyz ray, t_xyz viewpoint)
{
	t_location_transformation_information_station	transform;

	transform.rotation_angle = angle_between(v_normalize(axis),
			(t_xyz){0, 1, 0});
	transform.rotation = create_rotation_matrix(v_cross(axis,
				(t_xyz){0, 1, 0}), transform.rotation_angle);
	transform.to_local = local_matrix(axis, shape_centre,
			transform.rotation_angle);
	transform.local_ray = v_matrix_mul(transform.rotation, ray);
	transform.local_viewpoint = v_matrix_mul(transform.to_local, viewpoint);
	return (transform);
}
