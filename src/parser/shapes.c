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

static void	new_cylinder2(t_cylinder *cylinder, t_scene *scene);

int	new_sphere(char **raw_input, t_scene *scene)
{
	t_sphere	*sphere;

	if (strarray_size(raw_input) != 3)
		return (ft_perror("error: sphere: three sets of info needed"), FAIL);
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (FAIL);
	sphere->colour = NULL;
	sphere->centre = atoxyz(raw_input[0]);
	if (!sphere->centre)
		return (ft_perror("error: sphere: invalid centre"), FAIL);
	if (!ft_isfloat(raw_input[1]) || ft_atof(raw_input[1]) < 0.0)
		return (ft_perror("error: sphere: invalid diameter"), FAIL);
	sphere->diameter = ft_atof(raw_input[1]);
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
	t_plane	*plane;

	if (strarray_size(raw_input) != 3)
		return (ft_perror("error: plane: three sets of info needed"), FAIL);
	plane = ft_calloc(1, sizeof(t_plane));
	if (!plane)
		return (FAIL);
	plane->colour = NULL;
	plane->point = atoxyz(raw_input[0]);
	if (!plane->point)
		return (ft_perror("error: plane: invalid point"), FAIL);
	plane->norm = atoxyz(raw_input[1]);
	if (!plane->norm || !is_normalised(plane->norm))
		return (ft_perror("error: plane: invalid norm vector"), FAIL);
	plane->colour = atorgb(raw_input[2]);
	if (!plane->colour)
		return (ft_perror("error: plane: invalid RGB format"), FAIL);
	if (!(scene->planes))
		scene->planes = ft_lstnew(plane);
	else
		ft_lstadd_back(&(scene->planes), ft_lstnew(plane));
	return (OK);
}

int	new_cylinder(char **raw_input, t_scene *scene)
{
	t_cylinder	*cylinder;

	if (strarray_size(raw_input) != 5)
		return (ft_perror("error: cylinder: five sets info needed"), FAIL);
	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
		return (FAIL);
	cylinder->colour = NULL;
	cylinder->axis = NULL;
	cylinder->centre = atoxyz(raw_input[0]);
	if (!cylinder->centre)
		return (ft_perror("error: cylinder: invalid centre"), FAIL);
	cylinder->axis = atoxyz(raw_input[1]);
	if (!cylinder->axis || !is_normalised(cylinder->axis))
		return (ft_perror("error: cylinder: invalid axis"), FAIL);
	if (!ft_isfloat(raw_input[2]) || ft_atof(raw_input[2]) < 0.0f)
		return (ft_perror("error: cylinder: invalid diameter"), FAIL);
	cylinder->diameter = ft_atof(raw_input[2]);
	if (!ft_isfloat(raw_input[3]) || ft_atof(raw_input[3]) < 0.0f)
		return (ft_perror("error: cylinder: invalid height"), FAIL);
	cylinder->height = ft_atof(raw_input[3]);
	cylinder->colour = atorgb(raw_input[4]);
	if (!cylinder->colour)
		return (ft_perror("error: cylinder: invalid RGB format"), FAIL);
	return (new_cylinder2(cylinder, scene), OK);
}

static void	new_cylinder2(t_cylinder *cylinder, t_scene *scene)
{
	if (!(scene->cylinders))
		scene->cylinders = ft_lstnew(cylinder);
	else
		ft_lstadd_back(&(scene->cylinders), ft_lstnew(cylinder));
}
