/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 13:54:34 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/26 13:54:34 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

int	strarray_size(char **array)
{
	int	i;

	i = 0;
	if (!array[0])
		return (0);
	while (array[i])
		i++;
	return (i);
}

void	set_fov_y(t_vars *mlx_data, t_camera *camera)
{
	camera->fov_y = (double)camera->fov_x / mlx_data->aspect_ratio;
}
