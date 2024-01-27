/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 19:13:50 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/27 19:13:50 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

typedef struct s_matrix
{
	double	m[3][3];
}	t_matrix;

t_matrix	matrix_multiply(t_matrix m1, t_matrix m2);
t_xyz		m_v_multiply(t_matrix m, t_xyz in);
t_matrix	create_rotation_matrix(t_matrix result, t_xyz axis, double angle);
t_matrix	identity_matrix(void);

#endif
