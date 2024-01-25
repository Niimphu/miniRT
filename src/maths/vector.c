/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:11:27 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/10 14:05:53 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xyz.h"
#include <stdlib.h>
#include <math.h>

bool	is_normalised(t_xyz vector)
{
	if (vector.x < -1.0 || vector.x > 1.0 || vector.y < -1.0
		|| vector.y > 1.0 || vector.z < -1.0 || vector.z > 1.0)
		return (false);
	return (true);
}

double	v_length(t_xyz vector)
{
	return (sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2)));
}

t_xyz	v_normalize(t_xyz vector)
{
	double	l;
	t_xyz	result;

	l = v_length(vector);
	if (l == 0)
		return (vector);
	result.x = vector.x / l;
	result.y = vector.y / l;
	result.z = vector.z / l;
	return (result);
}

double	v_dot(t_xyz v1, t_xyz v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_xyz	v_cross(t_xyz v1, t_xyz v2)
{
	t_xyz	new;

	new.x = v1.y * v2.z - v1.z * v2.y;
	new.y = v1.z * v2.x - v1.x * v2.z;
	new.z = v1.x * v2.y - v1.y * v2.x;
	return (new);
}
