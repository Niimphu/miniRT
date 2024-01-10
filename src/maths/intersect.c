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

#include "xyz.h"
#include "miniRT.h"

t_intersect	*new_intersect(t_xyz point, double distance,
										void *shape, int type)
{
	t_intersect	*new;

	new = ft_calloc(1, sizeof(t_intersect));
	if (!new)
		return (NULL);
	new->point = point;
	new->distance = distance;
	new->shape = shape;
	new->type = type;
	return (new);
}