/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:07:01 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/09 16:56:01 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//DEBUG ONLY: NOT NEEDED FOR FINAL PROJECT

#include <stdio.h>
#include "printer.h"

void	print_scene_info(t_scene	*scene)
{
	t_list		*node;
	t_sphere	*sphere;
	t_plane		*plane;
	t_cylinder	*cylinder;

	node = NULL;
	printf("\n\n");
	printf("===== SCENE INFORMATION =====\n");
	printf("-----   Ambient Light   -----\n");
	if (scene->ambience)
	{
		printf("Lighting ratio: %.1f\nColour: ", scene->ambience->lighting);
		print_colour_info(scene->ambience->colour);
	}
	printf("-----      Camera      ------\n");
	printf("Viewpoint coordinates: ");
	print_coord_info(scene->camera->position);
	printf("3D normalised forward vector: ");
	print_vector_info(scene->camera->forward);
	printf("Field of view in degrees: %i\n", scene->camera->fov);
	printf("-----     Lighting      -----\n");
	if (scene->light)
	{
		printf("Light point coordinate: ");
		print_coord_info(scene->light->point);
		printf("Brightness ratio: %.1f\nColour: ", scene->light->brightness);
		print_colour_info(scene->light->colour);
	}
	printf("-----      Spheres      -----\n");
	if (scene->spheres)
	{
		node = scene->spheres;
		while (node)
		{
			sphere = (t_sphere *)node->content;
			printf("Centre coordinates: ");
			print_coord_info(sphere->centre);
			printf("Diameter: %.1f\nColour: ", sphere->diameter);
			print_colour_info(sphere->colour);
			if (node->next)
				printf("\n");
			node = node->next;
		}
		node = NULL;
	}
	printf("-----      Planes       -----\n");
	if (scene->planes)
	{
		node = scene->planes;
		while (node)
		{
			plane = (t_plane *)node->content;
			printf("Point on the plane: ");
			print_coord_info(plane->point);
			printf("3D normalised vector: ");
			print_vector_info(plane->norm);
			printf("Colour: ");
			print_colour_info(plane->colour);
			if (node->next)
				printf("\n");
			node = node->next;
		}
		node = NULL;
	}
	printf("-----     Cylinders     -----\n");
	if (scene->cylinders)
	{
		node = scene->cylinders;
		while (node)
		{
			cylinder = (t_cylinder *)node->content;
			printf("Centre coordinates: ");
			print_coord_info(cylinder->centre);
			printf("3D Normalised vector of axis: ");
			print_vector_info(cylinder->axis);
			printf("Diameter: %.1f\nHeight %.1f\nColour: ", cylinder->diameter,
				cylinder->height);
			print_colour_info(cylinder->colour);
			if (node->next)
				printf("\n");
			node = node->next;
		}
		node = NULL;
	}
	printf("=====        END        =====\n\n\n");
}

void	print_colour_info(t_rgb colour)
{
	printf("%i, %i, %i\n", colour.r, colour.g, colour.b);
}

void	print_coord_info(t_vector *vector)
{
	printf("(%.1f, %.1f, %.1f)\n", vector->x, vector->y, vector->z);
}

void	print_vector_info(t_vector *vector)
{
	printf("<%.1f, %.1f, %.1f>\n", vector->x, vector->y, vector->z);
}
