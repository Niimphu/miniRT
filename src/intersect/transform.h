/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 23:47:11 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/08 23:47:11 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raytrace/draw.h"
#include "../maths/matrix.h"

typedef struct s_location_transformation_information_station
{
	double		rotation_angle;
	t_matrix	to_local;
	t_matrix	rotation;
	t_xyz		local_viewpoint;
	t_xyz		local_ray;
}	t_location_transformation_information_station;

t_location_transformation_information_station	new_transform(t_xyz axis,
													t_xyz shape_centre,
													t_xyz ray, t_xyz viewpoint);
