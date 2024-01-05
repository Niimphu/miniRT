/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:29:29 by Kekuhne           #+#    #+#             */
/*   Updated: 2024/01/05 15:27:04 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_vector;

void		set_vector_to(t_vector *set, double x, double y, double z);
void		set_vector_to_single(t_vector *set, double n);

t_vector	cross(t_vector v1, t_vector v2);
double		dot(t_vector v1, t_vector v2);
t_vector	vector_normalize(t_vector vector);

t_vector	v_diff(t_vector v1, t_vector v2);

#endif