/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:41:58 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/13 16:25:12 by Kekuhne          ###   ########.fr       */
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

void	free_cone(void *node)
{
	t_cone	*cone;

	cone = (t_cone *)node;
	if (cone)
	{
		if (cone->centre)
			free(cone->centre);
		if (cone->axis)
			free(cone->axis);
		free(cone);
		cone = NULL;
	}
}

void	free_triangle(void *node)
{
	t_triangle	*triangle;

	triangle = (t_triangle *)node;
	if (triangle)
	{
		if (triangle->a)
			free(triangle->a);
		if (triangle->b)
			free(triangle->b);
		if (triangle->c)
			free(triangle->c);
		free(triangle);
		triangle = NULL;
	}
}
