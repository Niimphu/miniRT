/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:11:27 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/15 15:49:52 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xyz.h"
#include <stdlib.h>
#include <math.h>

double	v_angle(t_xyz v1, t_xyz v2)
{
	double	dot;
	double	length_v1;
	double	length_v2;

	dot = v_dot(v1, v2);
	length_v1 = v_length(v1);
	length_v2 = v_length(v2);
	return (acos(dot / (length_v1 * length_v2)));
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
