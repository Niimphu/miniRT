/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:11:03 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/27 18:11:03 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "miniRT.h"
#include "xyz.h"

static t_matrix	create_skew_symmetric_matrix(t_xyz axis);
static t_matrix	identity_matrix(void);

static t_matrix	identity_matrix(void)
{
	t_matrix	m;

	m.m[0][0] = 1.0;
	m.m[0][1] = 0.0;
	m.m[0][2] = 0.0;
	m.m[1][0] = 0.0;
	m.m[1][1] = 1.0;
	m.m[1][2] = 0.0;
	m.m[2][0] = 0.0;
	m.m[2][1] = 0.0;
	m.m[2][2] = 1.0;
	return (m);
}

t_xyz	m_v_multiply(t_matrix m, t_xyz in)
{
	t_xyz	out;

	out.x = m.m[0][0] * in.x + m.m[0][1] * in.y + m.m[0][2] * in.z;
	out.y = m.m[1][0] * in.x + m.m[1][1] * in.y + m.m[1][2] * in.z;
	out.z = m.m[2][0] * in.x + m.m[2][1] * in.y + m.m[2][2] * in.z;
	return (out);
}

t_matrix	create_rotation_matrix(t_matrix result, t_xyz axis, double angle)
{
	double		s;
	double		c;
	t_matrix	k;
	t_matrix	k2;
	t_matrix	i;

	if (angle < TOLERANCE)
		return (identity_matrix());
	i = identity_matrix();
	s = sin(angle);
	c = cos(angle);
	k = create_skew_symmetric_matrix(axis);
	k2 = matrix_multiply(k, k);
	result.m[0][0] = i.m[0][0] + s * k.m[0][0] + (1 - c) * k2.m[0][0];
	result.m[0][1] = i.m[0][1] + s * k.m[0][1] + (1 - c) * k2.m[0][1];
	result.m[0][2] = i.m[0][2] + s * k.m[0][2] + (1 - c) * k2.m[0][2];
	result.m[1][0] = i.m[1][0] + s * k.m[1][0] + (1 - c) * k2.m[1][0];
	result.m[1][1] = i.m[1][1] + s * k.m[1][1] + (1 - c) * k2.m[1][1];
	result.m[1][2] = i.m[1][2] + s * k.m[1][2] + (1 - c) * k2.m[1][2];
	result.m[2][0] = i.m[2][0] + s * k.m[2][0] + (1 - c) * k2.m[2][0];
	result.m[2][1] = i.m[2][1] + s * k.m[2][1] + (1 - c) * k2.m[2][1];
	result.m[2][2] = i.m[2][2] + s * k.m[2][2] + (1 - c) * k2.m[2][2];
	return (result);
}

t_matrix	create_skew_symmetric_matrix(t_xyz axis)
{
	t_matrix	m;

	m.m[0][0] = 0;
	m.m[0][1] = -1 * axis.z;
	m.m[0][2] = axis.y;
	m.m[1][0] = axis.z;
	m.m[1][1] = 0;
	m.m[1][2] = -1 * axis.x;
	m.m[2][0] = -1 * axis.y;
	m.m[2][1] = axis.x;
	m.m[2][2] = 0;
	return (m);
}

t_matrix	matrix_multiply(t_matrix m1, t_matrix m2)
{
	t_matrix	result;

	result.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] + m2.m[1][0];
	result.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] + m2.m[1][1];
	result.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] + m2.m[1][2];
	result.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] + m2.m[1][0];
	result.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] + m2.m[1][1];
	result.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] + m2.m[1][2];
	result.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] + m2.m[1][0];
	result.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] + m2.m[1][1];
	result.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] + m2.m[1][2];
	return (result);
}
