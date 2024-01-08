/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:41:58 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/15 19:41:58 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

void	free_sphere(void *node)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)node;
	if (sphere)
	{
		if (sphere->centre)
			free(sphere->centre);
		free(sphere);
		sphere = NULL;
	}
}

void	free_plane(void *node)
{
	t_plane	*plane;

	plane = (t_plane *)node;
	if (plane)
	{
		if (plane->point)
			free(plane->point);
		if (plane->norm)
			free(plane->norm);
		free(plane);
		plane = NULL;
	}
}

void	free_cylinder(void *node)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)node;
	if (cylinder)
	{
		if (cylinder->centre)
			free(cylinder->centre);
		if (cylinder->axis)
			free(cylinder->axis);
		free(cylinder);
		cylinder = NULL;
	}
}
