/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 16:53:31 by Kekuhne           #+#    #+#             */
/*   Updated: 2024/02/01 19:28:06 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "xyz.h"

t_matrix create_translation_matrix(double tx, double ty, double tz)
{
	t_matrix	m;

	m.m[0][0] = 1.0;
	m.m[0][1] = 0.0;
	m.m[0][2] = 0.0;
	m.m[0][3] = -tx;
	m.m[1][0] = 0.0;
	m.m[1][1] = 1.0;
	m.m[1][2] = 0.0;
	m.m[1][3] = -ty;
	m.m[2][0] = 0.0;
	m.m[2][1] = 0.0;
	m.m[2][2] = 1.0;
	m.m[2][3] = -tz;
	m.m[3][0] = 0.0;
	m.m[3][1] = 0.0;
	m.m[3][2] = 0.0;
	m.m[3][3] = 1.0;
	return (m);
}

static t_matrix	identity_matrix(void)
{
	t_matrix	m;

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

double angle_between(t_xyz v1, t_xyz v2)
{
	double	dot;
	double	length_v1;
	double	length_v2;

	dot = v_dot(v1, v2);
	length_v1 = v_length(v1);
	length_v2 = v_length(v2);
	return (acos(dot / (length_v1 * length_v2)));
}

t_matrix create_rotation_matrix(t_xyz axis, double angle)
{
	t_matrix	m;
	double		s;
	double		c;

	axis = v_normalize(axis);
	if (angle < 1e-6)
		return (identity_matrix());
	s = sin(angle);
	c = cos(angle);
	m.m[0][0] = (1.0 - c) * axis.x * axis.x + c;
	m.m[0][1] = (1.0 - c) * axis.x * axis.y - s * axis.z;
	m.m[0][2] = (1.0 - c) * axis.x * axis.z + s * axis.y;
	m.m[0][3] = 0;
	m.m[1][0] = (1.0 - c) * axis.x * axis.y + s * axis.z;
	m.m[1][1] = (1.0 - c) * axis.y * axis.y + c;
	m.m[1][2] = (1.0 - c) * axis.y * axis.z - s * axis.x;
	m.m[1][3] = 0;
	m.m[2][0] = (1.0 - c) * axis.x * axis.z - s * axis.y;
	m.m[2][1] = (1.0 - c) * axis.y * axis.z + s * axis.x;
	m.m[2][2] = (1.0 - c) * axis.z * axis.z + c;
	m.m[2][3] = 0;
	m.m[3][0] = 0;
	m.m[3][1] = 0;
	m.m[3][2] = 0;
	m.m[3][3] = 1;
	return (m);
}

t_xyz v_matrix_mul(t_matrix m, t_xyz in)
{
	t_xyz	out;

	out.x = m.m[0][0] * in.x + m.m[0][1] * in.y + m.m[0][2] * in.z + m.m[0][3] * 1;
	out.y = m.m[1][0] * in.x + m.m[1][1] * in.y + m.m[1][2] * in.z + m.m[1][3] * 1;
	out.z = m.m[2][0] * in.x + m.m[2][1] * in.y + m.m[2][2] * in.z + m.m[2][3] * 1;
	return (out);
}

t_matrix m_matrix_mul(t_matrix t, t_matrix r)
{
	t_matrix m;
	int i = 0;

    while (i < 4) {
        int j = 0;
        while (j < 4) {
            m.m[i][j] = 0.0;
            int k = 0;
            while (k < 4) {
                m.m[i][j] += t.m[i][k] * r.m[k][j];
                k++;
            }
            j++;
        }
        i++;
    }

    return m;
}

t_matrix	local_matrix(t_xyz axis, t_xyz center, double angle)
{
	t_matrix	r;
	t_matrix	t;
	t_matrix	m;

	axis = v_normalize(axis);
	t = create_translation_matrix(center.x, center.y, center.z);
	r = create_rotation_matrix(v_cross(axis, (t_xyz){0,1,0}), angle);
	m = m_matrix_mul(r, t);
	//printf("viewpoint is %f %f %f", viewpoint.x, viewpoint.y, viewpoint.z);
	//exit(1);
	return (m);
}

t_matrix	world_matrix(t_xyz axis, t_xyz center, double angle)
{
	t_matrix	r;
	t_matrix	t;
	t_matrix	m;

	axis = v_normalize(axis);
	center = v_invert(center);
	t = create_translation_matrix(center.x, center.y, center.z);
	r = create_rotation_matrix(v_cross((t_xyz){0,1,0}, axis), -angle);
	m = m_matrix_mul(t, r);
	//printf("viewpoint is %f %f %f", viewpoint.x, viewpoint.y, viewpoint.z);
	//exit(1);
	return (m);
}