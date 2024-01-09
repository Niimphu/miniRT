/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 20:37:40 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/09 20:37:40 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "vector.h"
#include "element.h"

t_vector	s_surface_normal(t_sphere *sphere, t_vector point)
{
	return (v_normalize(v_diff(point, *sphere->centre)));
}
