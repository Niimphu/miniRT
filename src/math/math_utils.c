/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:34:14 by Kekuhne           #+#    #+#             */
/*   Updated: 2024/01/09 16:19:25 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include <stdlib.h>
#include <math.h>
//probably should add a bool to keep or free the passed the t_vector

double	ft_sqr(double n)
{
	return (n * n);
}

t_vector	cpy_vector(t_vector *original)
{
	t_vector	copy;

	copy.x = original->x;
	copy.y = original->y;
	copy.z = original->z;
	return (copy);
}

void	set_vector_to(t_vector *set, double x, double y, double z)
{
	set->x = x;
	set->y = y;
	set->z = z;
}

void	set_vector_to_single(t_vector *set, double n)
{
	set->x = n;
	set->y = n;
	set->z = n;
}

double	vector_length(t_vector vector)
{
	return (ft_sqr(vector.x) + ft_sqr(vector.y) + ft_sqr(vector.z));
}

double	vector_length_sqr(t_vector vec)
{
	return (sqrt(vector_length(vec)));
}

t_vector	v_normalize(t_vector vector)
{
	double		l;
	t_vector	result;

	l = vector_length_sqr(vector);
	if (l == 0)
		return (vector);
	result.x = vector.x / l;
	result.y = vector.y / l;
	result.z = vector.z / l;
	return (result);
}

double	v_dot(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	v_cross(t_vector v1, t_vector v2)
{
	t_vector	new;

	new.x = v1.y * v2.z - v1.z * v2.y;
	new.y = v1.z * v2.x - v1.x * v2.z;
	new.z = v1.x * v2.y - v1.y * v2.x;
	return (new);
}

t_vector	v_add(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vector	v_subtract(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vector	v_invert(t_vector v)
{
	return (v_scale(v, -1.0));
}

t_vector	v_scale(t_vector v, double factor)
{
	t_vector	result;

	result.x = v.x * factor;
	result.y = v.y * factor;
	result.z = v.z * factor;
	return (result);
}

t_vector	v_diff(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

//t_vector	vector_negativ(t_vector *v)
//{
//	t_vector	new;
//
//	set_vector_to(&new,
//		v->x *= -1,
//		v->y *= -1,
//		v->z *= -1);
//	return (new);
//}
