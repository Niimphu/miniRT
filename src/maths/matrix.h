/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:13:50 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/02 17:24:54 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "xyz.h"

typedef struct s_matrix
{
	double m[4][4];
}	t_matrix;

t_matrix	create_translation_matrix(double tx, double ty, double tz);
t_matrix	create_rotation_matrix(t_xyz axis, double angle);
double		angle_between(t_xyz v1, t_xyz v2);
t_xyz		v_matrix_mul(t_matrix m, t_xyz in);
t_matrix	local_matrix(t_xyz axis, t_xyz center, double angle);

t_matrix	m_matrix_mul(t_matrix t, t_matrix r);
t_matrix	identity_matrix(void);

#endif
