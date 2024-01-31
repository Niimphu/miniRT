/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xyz.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:11:27 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/31 13:51:49 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XYZ_H
# define XYZ_H

# include <stdbool.h>
# include "colour.h"

typedef struct s_xyz
{
	double	x;
	double	y;
	double	z;
}			t_xyz;

typedef struct s_intersect
{
	bool	valid;
	t_xyz	point;
	t_rgb	colour;
	double	distance;
	void	*shape;
	int		type;
}				t_intersect;

typedef struct s_matrix
{
	double m[3][3];
}	t_matrix;

t_xyz		v_cross(t_xyz v1, t_xyz v2);
double		v_dot(t_xyz v1, t_xyz v2);
t_xyz		v_normalize(t_xyz vector);
double		v_length(t_xyz vector);

t_xyz		v_subtract(t_xyz v1, t_xyz v2);
t_xyz		v_scale(t_xyz v, double factor);
t_xyz		v_add(t_xyz v1, t_xyz v2);
t_xyz		v_invert(t_xyz v);
t_xyz 		v_matrix_mul(t_matrix m, t_xyz in);

double		p2p_distance(t_xyz a, t_xyz b);

t_intersect	new_intersect(void);

t_matrix	create_transform_matrix(double tx, double ty, double tz);
double		angle_between(t_xyz v1, t_xyz v2);
t_matrix	create_rotation_matrix(t_xyz axis, double angle);
t_matrix	inverse_matrix(t_matrix m);
#endif
