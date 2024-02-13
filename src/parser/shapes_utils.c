/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:34:20 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/05 16:51:19 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_material	create_material(char **input)
{
	t_material	material;

	material.spec_coeff = ft_atod(input[0]);
	material.shininess = ft_atoi(input[1]);
	material.reflectivity = ft_atod(input[2]);
	return (material);
}

void	add_shape(t_scene *scene, void *shape, int type)
{
	if (type == SPHERE)
	{
		if (!(scene->spheres))
			scene->spheres = ft_lstnew(shape);
		else
			ft_lstadd_back(&(scene->spheres), ft_lstnew(shape));
	}
	else if (type == PLANE)
	{
		if (!(scene->planes))
			scene->planes = ft_lstnew(shape);
		else
			ft_lstadd_back(&(scene->planes), ft_lstnew(shape));
	}
	else if (type == CYLINDER)
	{
		if (!(scene->cylinders))
			scene->cylinders = ft_lstnew(shape);
		else
			ft_lstadd_back(&(scene->cylinders), ft_lstnew(shape));
	}
}

void	add_cone(t_scene *scene, void *shape)
{
	if (!(scene->cone))
		scene->cone = ft_lstnew(shape);
	else
		ft_lstadd_back(&(scene->cone), ft_lstnew(shape));
}
