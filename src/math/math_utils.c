/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:34:14 by Kekuhne           #+#    #+#             */
/*   Updated: 2023/12/06 19:25:52 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_utils.h"
#include <stdlib.h>
#include <math.h>
//probably should add a bool to keep or free the passed the t_vector

float	ft_sqr(float n)
{
	return (n * n);
}

t_vector	*new_vector(void)
{
	t_vector	*new;

	new = malloc(sizeof(t_vector));
	if (!new)
		return (NULL);
	new->x = 0.0;
	new->y = 1.0;
	new->z = 0.0;
	return (new);
}

t_vector	*cpy_vector(t_vector *cpy)
{
	t_vector	*new;

	new = malloc(sizeof(t_vector));
	if (!new)
		return (NULL);
	new->x = cpy->x;
	new->y = cpy->y;
	new->z = cpy->z;
	return (new);
}

void	set_vector_to(t_vector *set, float x, float y, float z)
{
	set->x = x;
	set->y = y;
	set->z = z;
}

void	set_vector_to_single(t_vector *set, float n)
{
	set->x = n;
	set->y = n;
	set->z = n;
}

void	free_vector(t_vector *del)
{
	free(del);
}

float	vector_lenght(t_vector *vec)
{
	return (ft_sqr(vec->x) + ft_sqr(vec->y) + ft_sqr(vec->z));
}

float	vector_lenght_sqr(t_vector *vec)
{
	return ((float)sqrt(vector_lenght(vec)));
}

float	vector_normalize(t_vector *vec)
{
	float	l;

	l = vector_lenght(vec);
	if (l != 0)
	{
		vec->x /= l;
		vec->y /= l;
		vec->z /= l;
	}
	return (l);
}

t_vector	*cpy_vector_normalize(t_vector *vec)
{
	t_vector	*new;

	new = cpy_vector(vec);
	if (!new)
		return (NULL);
	vector_normalize(new);
	return (new);
}

float	dot(t_vector *v1, t_vector *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vector	*cross(t_vector *v1, t_vector *v2)
{
	t_vector	*new;

	new = new_vector();
	if (!new)
		return (NULL);
	set_vector_to(new,
		v1->y * v2->z - v1->z * v2->y,
		v1->z * v2->x - v1->x * v2->z,
		v1->x * v2->y - v1->y * v2->x);
	return (new);
}

t_vector	*vector_add(t_vector *v1, t_vector *v2)
{
	t_vector	*new;

	new = new_vector();
	if (!new)
		return (NULL);
	set_vector_to(new,
		v1->x + v2->x,
		v1->y + v2->y,
		v1->z + v2->z);
	return (NULL);
}

t_vector	*vector_sub(t_vector *v1, t_vector *v2)
{
	t_vector	*new;

	new = new_vector();
	if (!new)
		return (NULL);
	set_vector_to(new,
		v1->x - v2->x,
		v1->y - v2->y,
		v1->z - v2->z);
	return (NULL);
}

t_vector	*vector_mul(t_vector *v, float f)
{
	t_vector	*new;

	new = new_vector();
	if (!new)
		return (NULL);
	set_vector_to(new,
		v->x *= f,
		v->y *= f,
		v->z *= f);
	return (new);
}

t_vector	*vector_div(t_vector *v, float f)
{
	t_vector	*new;

	new = new_vector();
	if (!new)
		return (NULL);
	set_vector_to(new,
		v->x /= f,
		v->y /= f,
		v->z /= f);
	return (new);
}

t_vector	*vector_negativ(t_vector *v)
{
	t_vector	*new;

	new = new_vector();
	if (!new)
		return (NULL);
	set_vector_to(new,
		v->x *= -1,
		v->y *= -1,
		v->z *= -1);
	return (new);
}
