/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msaa.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:52:36 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/15 18:24:58 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MSAA_H
# define MSAA_H

# include "../../lib/miniRT.h"
# include "../intersect/intersect.h"
# include "../maths/xyz.h"
# include "../colour/colour.h"

typedef struct s_msaa
{
	t_xyz		rays[4];
	t_intersect	intersects[4];
	int			colours[4];
}			t_msaa;

void	draw_closest_shape_msaa(t_vars *mlx, t_camera *camera, t_rt *rt);
t_rgb	average_4colour(t_rgb a, t_rgb b, t_rgb c, t_rgb d);

#endif
