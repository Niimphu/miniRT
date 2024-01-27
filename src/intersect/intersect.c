/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:42:11 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/10 14:00:05 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "intersect.h"
#include "../maths/xyz.h"
#include "../../lib/miniRT.h"

t_intersect	new_intersect(void)
{
	t_intersect	new;

	new.valid = false;
	new.point = (t_xyz){0};
	new.colour = (t_rgb){0};
	new.distance = 0.0;
	new.shape = NULL;
	new.type = 0;
	new.material = (t_material){0};
	return (new);
}