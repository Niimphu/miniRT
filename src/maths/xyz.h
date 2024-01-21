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

# define TOLERANCE 0.0001

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}			t_xyz;

typedef struct s_intersect
{
	bool		valid;
	t_xyz		point;
	t_rgb		colour;
	double		distance;
	void		*shape;
	int			type;
	t_material	material;
}				t_intersect;

t_xyz		v_cross(t_xyz v1, t_xyz v2);
double		v_dot(t_xyz v1, t_xyz v2);
t_xyz		v_normalize(t_xyz vector);
double		v_length(t_xyz vector);

t_xyz		v_subtract(t_xyz v1, t_xyz v2);
t_xyz		v_scale(t_xyz v, double factor);
t_xyz		v_add(t_xyz v1, t_xyz v2);
t_xyz		v_invert(t_xyz v);

double		p2p_distance(t_xyz a, t_xyz b);
bool		p_equal(t_xyz a, t_xyz b);

t_intersect	new_intersect(void);

#endif
