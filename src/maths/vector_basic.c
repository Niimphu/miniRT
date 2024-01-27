/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:15:11 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/10 14:15:11 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xyz.h"

bool	is_normalised(t_xyz vector)
{
	if (vector.x < -1.0 || vector.x > 1.0 || vector.y < -1.0
		|| vector.y > 1.0 || vector.z < -1.0 || vector.z > 1.0)
		return (false);
	return (true);
}

t_xyz	v_add(t_xyz v1, t_xyz v2)
{
	t_xyz	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_xyz	v_subtract(t_xyz v1, t_xyz v2)
{
	t_xyz	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_xyz	v_invert(t_xyz v)
{
	return (v_scale(v, -1.0));
}

t_xyz	v_scale(t_xyz v, double factor)
{
	t_xyz	result;

	result.x = v.x * factor;
	result.y = v.y * factor;
	result.z = v.z * factor;
	return (result);
}
