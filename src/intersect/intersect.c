/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 18:42:11 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/03 14:45:50 by Kekuhne          ###   ########.fr       */
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
	new.point_normal = (t_xyz){0};
	new.colour = (t_rgb){0};
	new.distance = 0.0;
	new.shape = NULL;
	new.type = 0;
	new.material = (t_material){0};
	return (new);
}
