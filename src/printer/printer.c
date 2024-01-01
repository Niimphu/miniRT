/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:07:01 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/01 17:20:20 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//DEBUG ONLY: NOT NEEDED FOR FINAL PROJECT

#include <stdio.h>
#include "printer.h"

void	print_scene_info(t_scene	*scene)
{
	printf("\n\n");
	printf("===== SCENE INFORMATION =====\n");
	printf("-----   Ambient Light   -----\n");
	if (scene->ambience)
	{
		printf("Lighting ratio: %f\nColour: ", scene->ambience->lighting);
		print_colour_info(scene->ambience->colour);
	}
	printf("-----      Camera      ------\n");
	printf("Viewpoint: ");
	print_coord_info(scene->camera->view_point);
	printf("Orientation: ");
	print_vector_info(scene->camera->orientation);
	printf("Field of view: %i\n", scene->camera->fov);
	printf("-----     Lighting      -----\n");
	if (scene->light)
	{

	}
}

void	print_colour_info(t_rgb *colour)
{
	printf("%i, %i, %i\n", colour->r, colour->g, colour->b);
}

void	print_coord_info(t_vector *vector)
{
	printf("(%f, %f, %f)\n", vector->x, vector->y, vector->z);
}

void	print_vector_info(t_vector *vector)
{
	printf("<%f, %f, %f>\n", vector->x, vector->y, vector->z);
}
