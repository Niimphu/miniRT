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
		if ((*ambience)->colour)
			free((*ambience)->colour);
		free(*ambience);
		ambience = NULL;
	}
}
