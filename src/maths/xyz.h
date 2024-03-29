/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xyz.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:11:27 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/13 16:18:27 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XYZ_H
# define XYZ_H

# include <stdbool.h>
# include "../colour/colour.h"
# include "../../lib/material.h"

typedef struct s_xyz
{
	double	x;
	double	y;
	double	z;
}			t_xyz;

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

#endif
