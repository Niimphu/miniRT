/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:11:27 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/09 18:40:39 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:29:29 by Kekuhne           #+#    #+#             */
/*   Updated: 2024/01/09 16:19:25 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vector;

typedef struct s_intersect
{
	t_vector	point;
	double		distance;
	void		*shape;
	int			type;
}				t_intersect;

void		set_vector_to(t_vector *set, double x, double y, double z);
void		set_vector_to_single(t_vector *set, double n);

t_vector	v_cross(t_vector v1, t_vector v2);
double		v_dot(t_vector v1, t_vector v2);
t_vector	v_normalize(t_vector vector);

t_vector	v_diff(t_vector v1, t_vector v2);
t_vector	v_scale(t_vector v, double factor);
t_vector	v_add(t_vector v1, t_vector v2);
t_vector	v_invert(t_vector v);

double		distance_between(t_vector a, t_vector b);

t_intersect	*new_intersect(t_vector point, double distance, void *shape, int type);

#endif