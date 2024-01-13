/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:13:20 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/10 14:13:20 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "xyz.h"

double	p2p_distance(t_xyz a, t_xyz b)
{
	double	distance;

	distance = sqrt(pow(b.x - a.x, 2) + pow(b.y - a.y, 2) + pow(b.z - a.z, 2));
	return (distance);
}

bool	p_equal(t_xyz a, t_xyz b)
{
	return ((fabs(a.x - b.x) < TOLERANCE) && (fabs(a.y - b.y) < TOLERANCE)
		&& (fabs(a.z - b.z) < TOLERANCE));
}
