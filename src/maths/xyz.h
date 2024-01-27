/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:11:27 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/21 16:30:56 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XYZ_H
# define XYZ_H

# include <stdbool.h>
# include "colour.h"
# include "../../lib/material.h"

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_xyz;

typedef struct s_matrix
{
	double	m[3][3];
}	t_matrix;

t_xyz		v_cross(t_xyz v1, t_xyz v2);
double		v_dot(t_xyz v1, t_xyz v2);
t_xyz		v_normalize(t_xyz vector);
double		v_length(t_xyz vector);
bool		is_normalised(t_xyz vector);

t_xyz		v_subtract(t_xyz v1, t_xyz v2);
t_xyz		v_scale(t_xyz v, double factor);
t_xyz		v_add(t_xyz v1, t_xyz v2);
t_xyz		v_invert(t_xyz v);

double		p2p_distance(t_xyz a, t_xyz b);
bool		p_equal(t_xyz a, t_xyz b);

double		v_angle(t_xyz v1, t_xyz v2);
t_matrix	matrix_multiply(t_matrix m1, t_matrix m2);

#endif
