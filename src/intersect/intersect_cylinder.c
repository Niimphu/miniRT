/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:08:30 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/27 18:08:30 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../raytrace/draw.h"

t_intersect	ray_intersects_cylinder(t_xyz *viewpoint, t_xyz ray,
					t_cylinder *cylinder)
{
	(void)viewpoint;
	(void)ray;
	(void)cylinder;
	return (new_intersect());
}
