/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:58:24 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/20 21:58:24 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	new_sphere(char **raw_input, t_scene *scene)
{
	t_sphere	*sphere;

	if (strarray_size(raw_input) != 3)
		return (ft_perror("error: sphere: three sets of info required"),
			FAIL);
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (FAIL);
	sphere->colour = NULL;
	sphere->centre = atoxyz(raw_input[0]);
	if (!sphere->centre)
		return (ft_perror("error: sphere: invalid light point"), FAIL);
	if (!ft_isfloat(raw_input[1]))
		return (ft_perror("error: sphere: invalid diameter"), FAIL);
	sphere->diameter = ft_atof(raw_input[1]);
	if (sphere->diameter < 0.0)
		return (ft_perror("error: sphere: invalid diameter"), FAIL);
	sphere->colour = atorgb(raw_input[2]);
	if (!sphere->colour)
		return (ft_perror("error: sphere: invalid RGB format"), FAIL);
	if (!(scene->spheres))
		scene->spheres = ft_lstnew(sphere);
	else
		ft_lstadd_back(&(scene->spheres), ft_lstnew(sphere));
	return (OK);
}

int	new_plane(char **raw_input, t_scene *scene)
{
	(void)raw_input;
	(void)scene;
	return (OK);
}

int	new_cylinder(char **raw_input, t_scene *scene)
{
	(void)raw_input;
	(void)scene;
	return (OK);
}
