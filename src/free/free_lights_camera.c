/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lights_camera.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:41:49 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/15 19:41:49 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	free_ambience(t_ambience **ambience)
{
	if (*ambience)
	{
		free(*ambience);
		ambience = NULL;
	}
}

void	free_camera(t_camera **camera)
{
	if (*camera)
	{
		if ((*camera)->view_point)
			free((*camera)->view_point);
		if ((*camera)->orientation)
			free((*camera)->orientation);
		free(*camera);
		camera = NULL;
	}
}

void	free_light(t_light **light)
{
	if (*light)
	{
		if ((*light)->point)
			free((*light)->point);
		free(*light);
		light = NULL;
	}
}
