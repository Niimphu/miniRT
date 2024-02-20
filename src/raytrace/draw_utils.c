/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 18:32:36 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/13 18:32:36 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "draw.h"

void	calculate_camera_right_up(t_camera *camera)
{
	if (camera->forward->x == 0 && camera->forward->y == 0)
		camera->right = (t_xyz){1, 0, 0};
	else
		camera->right = v_normalize(v_cross(*camera->forward,
					(t_xyz){0, 1, 0}));
	camera->up = v_normalize(v_cross(camera->right, *camera->forward));
	camera->right = v_invert(camera->right);
}
