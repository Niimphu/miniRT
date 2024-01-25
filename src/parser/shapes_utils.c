/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:34:20 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/25 15:34:20 by yiwong           ###   ########.fr       */
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
