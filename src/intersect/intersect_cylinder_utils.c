/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 17:58:33 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/18 17:58:33 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "transform.h"
#include "../maths/matrix.h"
#include "intersect.h"

static t_intersect	get_closer_buddy(t_intersect first, t_intersect second);

t_intersect	closest_side(t_xyz distances, t_cylinder *cylinder,
				t_location_transformation_information_station t)
{
	t_intersect	first;
	t_intersect	second;

	first = new_intersect();
	second = new_intersect();
	if (distances.x > TOLERANCE)
	{
		first.distance = distances.x;
		first.point = v_add(t.local_viewpoint,
				v_scale(t.local_ray, distances.x));
		if (first.point.y < cylinder->height / 2
			&& first.point.y > cylinder->height / -2)
			first.valid = true;
	}
	if (distances.y > TOLERANCE)
	{
		second.distance = distances.y;
		second.point = v_add(t.local_viewpoint,
				v_scale(t.local_ray, distances.y));
		if (second.point.y < cylinder->height / 2
			&& second.point.y > cylinder->height / -2)
			second.valid = true;
	}
	return (get_closer_buddy(first, second));
}

static t_intersect	get_closer_buddy(t_intersect first, t_intersect second)
{
	t_intersect	closest;

	if (!second.valid)
		closest = first;
	else if (!first.valid)
		closest = second;
	else
	{
		if (first.distance < second.distance)
			closest = first;
		else
			closest = second;
	}
	return (closest);
}
