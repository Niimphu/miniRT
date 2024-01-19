/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_lights_camera.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:41:49 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/09 16:56:01 by yiwong           ###   ########.fr       */
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
		if ((*camera)->position)
			free((*camera)->position);
		if ((*camera)->forward)
			free((*camera)->forward);
		free(*camera);
		camera = NULL;
	}
}

void	free_light(void *node)
{
	t_light	*light;

	light = (t_light *)node;
	if (light)
	{
		if (light->point)
			free(light->point);
		free(light);
		light = NULL;
	}
}
