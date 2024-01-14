/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:53:31 by Kekuhne           #+#    #+#             */
/*   Updated: 2024/01/13 21:09:51 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "xyz.h"

t_matrix create_4x4_matrix(double tx, double ty, double tz)
{
	t_matrix	m;

	m.m[0][0] = 1.0;
	m.m[0][1] = 0.0;
	m.m[0][2] = 0.0;
	m.m[0][3] = tx;
	m.m[1][0] = 0.0;
	m.m[1][1] = 1.0;
	m.m[1][2] = 0.0;
	m.m[1][3] = ty;
	m.m[2][0] = 0.0;
	m.m[2][1] = 0.0;
	m.m[2][2] = 1.0;
	m.m[2][3] = tz;
	m.m[3][0] = 0.0;
	m.m[3][1] = 0.0;
	m.m[3][2] = 0.0;
	m.m[3][3] = 1.0;
	return (m);
}

static t_matrix identity_rot_matrix(void)
{
	t_matrix m;
	
	m.m[0][0] = 1.0;
	m.m[0][1] = 0.0;
	m.m[0][2] = 0.0;
	m.m[0][3] = 0.0;
	m.m[1][0] = 0.0;
	m.m[1][1] = 1.0;
	m.m[1][2] = 0.0;
	m.m[1][3] = 0.0;
	m.m[2][0] = 0.0;
	m.m[2][1] = 0.0;
	m.m[2][2] = 1.0;
	m.m[2][3] = 0.0;
	m.m[3][0] = 0.0;
	m.m[3][1] = 0.0;
	m.m[3][2] = 0.0;
	m.m[3][3] = 1.0;
	return (m);
}

t_matrix rotation_matrix(t_xyz axis, float angle)
{
	t_matrix out;
	axis = v_normalize(axis);
	float cos_theta;
	float sin_theta;
	float one_minus_cos_theta;

	cos_theta = cosf(angle);
	sin_theta = sinf(angle);
	one_minus_cos_theta = 1.0f - cos_theta;
	out = identity_rot_matrix();
	out.m[0][0] = cos_theta + axis.x * axis.x * one_minus_cos_theta;
	out.m[1][0] = axis.x * axis.y * one_minus_cos_theta - axis.z * sin_theta;
	out.m[2][0] = axis.x * axis.z * one_minus_cos_theta + axis.y * sin_theta;
	out.m[0][1] = axis.y * axis.x * one_minus_cos_theta + axis.z * sin_theta;
	out.m[1][1] = cos_theta + axis.y * axis.y * one_minus_cos_theta;
	out.m[2][1] = axis.y * axis.z * one_minus_cos_theta - axis.x * sin_theta;
	out.m[0][2] = axis.z * axis.x * one_minus_cos_theta - axis.y * sin_theta;
	out.m[1][2] = axis.z * axis.y * one_minus_cos_theta + axis.x * sin_theta;
	out.m[2][2] = cos_theta + axis.z * axis.z * one_minus_cos_theta;
	return (out);
}

t_matrix matrix_minor(const t_matrix *m, int row, int col)
{
    t_matrix minor;
    int i, j, x, y;

    for (i = 0, x = 0; i < 4; ++i)
    {
        if (i == row)
            continue;

        for (j = 0, y = 0; j < 4; ++j)
        {
            if (j == col)
                continue;

            minor.m[x][y] = m->m[i][j];
            ++y;
        }

        ++x;
    }

    return minor;
}

t_xyz v_matrix_mul(t_matrix m, t_xyz *in)
{
	t_xyz	out;
	int		i;
	int		j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		out.x = 0.0;
		out.y = 0.0;
		out.z = 0.0;
		while (j < 3)
		{
			if (j == 0)
				j = in->x;
			if (j == 1)
				j = in->y;
			if (j == 2)
				j = in->z;
			out.x += (m.m[i][j] * j);
			out.y += (m.m[i][j] * j);
			out.z += (m.m[i][j] * j);
			j++;
		}
		out.y = m.m[i][3];
		out.x = m.m[i][3];
		out.z = m.m[i][3];
		i++;
	}
	return (out);
}

t_matrix	inverse_matrix(t_matrix m)
{
	t_matrix	result;
	float		det;
	int			i;
	int			j;
	int			sign;

	det = 0.0f;
	i = 0;
	sign = 1;
	while (i < 4)
	{
		if (i % 2 == 0)
			sign = 1;
		else
			sign = -1;
		det += sign * m.m[0][i] * (m.m[1][(i + 1) % 4] * (m.m[2][(i + 2) % 4] * m.m[3][(i + 3) % 4] - m.m[2][(i + 3) % 4] * m.m[3][(i + 2) % 4]) - m.m[1][(i + 2) % 4] * (m.m[2][(i + 1) % 4] * m.m[3][(i + 3) % 4] - m.m[2][(i + 3) % 4] * m.m[3][(i + 1) % 4]));
		i++;
	}
	if (fabs(det) < 1e-8)
		return (identity_rot_matrix());
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if ((i + j) % 2 == 0)
				sign = 1;
			else
				sign = -1;
			result.m[j][i] = sign * matrix_minor(&m, i, j) / det;
			j++;
		}
		i++;
	}
	return (result);
}