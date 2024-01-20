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

static void			add_shape(t_scene *scene, void *shape, int type);
static t_cylinder	*cylinder_extended(char **raw_input, t_cylinder *cylinder,
						size_t info_count);

int	new_sphere(char **raw_input, t_scene *scene)
{
	t_sphere	*sphere;
	size_t		info_count;

	info_count = strarray_size(raw_input);
	if (info_count != 3 && info_count != 4)
		return (ft_perror("Error\nSphere: invalid parameter count"));
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (FAIL);
	if (!ft_isdouble(raw_input[1]) || ft_atod(raw_input[1]) < 0.0)
		return (free(sphere), ft_perror("Error\nSphere: invalid diameter"));
	sphere->diameter = ft_atod(raw_input[1]);
	sphere->colour = atorgb(raw_input[2]);
	if (!is_valid_rgb(sphere->colour))
		return (free(sphere), ft_perror("Error\nSphere: invalid colour"));
	sphere->centre = atoxyz(raw_input[0]);
	if (!sphere->centre)
		return (free(sphere), ft_perror("Error\nSphere: invalid centre"));
	if (info_count == 3)
		return (sphere->shininess = 0, add_shape(scene, sphere, SPHERE), OK);
	if (!ft_isdouble(raw_input[3]))
		return (free_sphere(sphere),
			ft_perror("Error\nSphere: invalid shininess"));
	sphere->shininess = ft_atod(raw_input[3]);
	return (add_shape(scene, sphere, SPHERE), OK);
}

int	new_plane(char **raw_input, t_scene *scene)
{
	t_plane	*plane;
	size_t	info_count;

	info_count = strarray_size(raw_input);
	if (info_count != 3 && info_count != 4)
		return (ft_perror("Error\nPlane: invalid parameter count"));
	plane = ft_calloc(1, sizeof(t_plane));
	if (!plane)
		return (FAIL);
	plane->norm = atoxyz(raw_input[1]);
	if (!plane->norm || !is_normalised(plane->norm))
		return (free(plane), ft_perror("Error\nPlane: invalid norm vector"));
	plane->colour = atorgb(raw_input[2]);
	if (!is_valid_rgb(plane->colour))
		return (free(plane), ft_perror("Error\nPlane: invalid colour"));
	plane->point = atoxyz(raw_input[0]);
	if (!plane->point)
		return (free(plane), ft_perror("Error\nPlane: invalid point"));
	if (info_count == 3)
		return (plane->shininess = 0, add_shape(scene, plane, PLANE), OK);
	if (!ft_isdouble(raw_input[3]))
		return (free_plane(plane),
			ft_perror("Error\nPlane: invalid shininess"));
	plane->shininess = ft_atod(raw_input[3]);
	return (add_shape(scene, plane, PLANE), OK);
}

int	new_cylinder(char **raw_input, t_scene *scene)
{
	t_cylinder	*cylinder;
	size_t		info_count;

	info_count = strarray_size(raw_input);
	if (info_count != 5 && info_count != 6)
		return (ft_perror("Error\nCylinder: invalid parameter count"));
	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
		return (FAIL);
	if (!ft_isdouble(raw_input[2]) || ft_atod(raw_input[2]) < 0.0f)
		return (free(cylinder), ft_perror("Error\nCylinder: \
			invalid diameter"));
	cylinder->diameter = ft_atod(raw_input[2]);
	if (!ft_isdouble(raw_input[3]) || ft_atod(raw_input[3]) < 0.0f)
		return (free(cylinder), ft_perror("Error\nCylinder: invalid height"));
	cylinder->height = ft_atod(raw_input[3]);
	cylinder->colour = atorgb(raw_input[4]);
	if (!is_valid_rgb(cylinder->colour))
		return (free(cylinder), ft_perror("Error\nCylinder: invalid colour"));
	cylinder = cylinder_extended(raw_input, cylinder, info_count);
	if (!cylinder)
		return (FAIL);
	return (add_shape(scene, cylinder, CYLINDER), OK);
}

static t_cylinder	*cylinder_extended(char **raw_input, t_cylinder *cylinder,
							size_t info_count)
{
	cylinder->axis = NULL;
	cylinder->centre = atoxyz(raw_input[0]);
	if (!cylinder->centre)
		return (free(cylinder), ft_perror("Error\nCylinder: invalid centre"),
			NULL);
	cylinder->axis = atoxyz(raw_input[1]);
	if (!cylinder->axis || !is_normalised(cylinder->axis))
		return (free_cylinder(cylinder),
			ft_perror("Error\nCylinder: invalid axis"), NULL);
	if (info_count == 5)
		return (cylinder->shininess = 0, cylinder);
	if (!ft_isdouble(raw_input[3]))
		return (free_cylinder(cylinder), ft_perror("Error\nCylinder: \
			invalid shininess"), NULL);
	cylinder->shininess = ft_atod(raw_input[3]);
	return (cylinder);
}

static void	add_shape(t_scene *scene, void *shape, int type)
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
