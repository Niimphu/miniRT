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
#include "material.h"

static t_cylinder	*cylinder_extended(char **input, t_cylinder *cylinder,
						size_t info_count);

int	new_sphere(char **input, t_scene *scene)
{
	t_sphere	*sphere;
	size_t		info_count;

	info_count = strarray_size(input);
	if (info_count != 3 && info_count != 6)
		return (error("Error\nSphere: invalid parameter count"));
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (FAIL);
	if (!ft_isdouble(input[1]) || ft_atod(input[1]) < 0.0)
		return (free(sphere), error("Error\nSphere: invalid diameter"));
	sphere->diameter = ft_atod(input[1]);
	sphere->colour = atorgb(input[2]);
	if (!is_valid_rgb(sphere->colour))
		return (free(sphere), error("Error\nSphere: invalid colour"));
	sphere->centre = atoxyz(input[0]);
	if (!sphere->centre)
		return (free(sphere), error("Error\nSphere: invalid centre"));
	if (info_count == 3)
		return (sphere->material = (t_material){0},
				add_shape(scene, sphere, SPHERE), OK);
	if (!is_valid_material(input + 3))
		return (free_sphere(sphere), error("Error\nSphere: invalid material"));
	sphere->material = create_material(input + 3);
	return (add_shape(scene, sphere, SPHERE), OK);
}

int	new_plane(char **input, t_scene *scene)
{
	t_plane	*plane;
	size_t	info_count;

	info_count = strarray_size(input);
	if (info_count != 3 && info_count != 6)
		return (error("Error\nPlane: invalid parameter count"));
	plane = ft_calloc(1, sizeof(t_plane));
	if (!plane)
		return (FAIL);
	plane->norm = atoxyz(input[1]);
	if (!plane->norm || !is_normalised(*plane->norm))
		return (free(plane), error("Error\nPlane: invalid norm vector"));
	plane->colour = atorgb(input[2]);
	if (!is_valid_rgb(plane->colour))
		return (free(plane), error("Error\nPlane: invalid colour"));
	plane->point = atoxyz(input[0]);
	if (!plane->point)
		return (free(plane), error("Error\nPlane: invalid point"));
	if (info_count == 3)
		return (plane->material = (t_material){0},
				add_shape(scene, plane, PLANE), OK);
	if (!is_valid_material(input + 3))
		return (free_plane(plane), error("Error\nPlane: invalid material"));
	plane->material = create_material(input + 3);
	return (add_shape(scene, plane, PLANE), OK);
}

int	new_cylinder(char **input, t_scene *scene)
{
	t_cylinder	*cylinder;
	size_t		info_count;

	info_count = strarray_size(input);
	if (info_count != 5 && info_count != 8)
		return (error("Error\nCylinder: invalid parameter count"));
	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
		return (FAIL);
	if (!ft_isdouble(input[2]) || ft_atod(input[2]) < 0.0f)
		return (free(cylinder), error("Error\nCylinder: \
			invalid diameter"));
	cylinder->diameter = ft_atod(input[2]);
	if (!ft_isdouble(input[3]) || ft_atod(input[3]) < 0.0f)
		return (free(cylinder), error("Error\nCylinder: invalid height"));
	cylinder->height = ft_atod(input[3]);
	cylinder->colour = atorgb(input[4]);
	if (!is_valid_rgb(cylinder->colour))
		return (free(cylinder), error("Error\nCylinder: invalid colour"));
	cylinder = cylinder_extended(input, cylinder, info_count);
	if (!cylinder)
		return (FAIL);
	return (add_shape(scene, cylinder, CYLINDER), OK);
}

static t_cylinder	*cylinder_extended(char **input, t_cylinder *cylinder,
							size_t info_count)
{
	cylinder->axis = NULL;
	cylinder->centre = atoxyz(input[0]);
	if (!cylinder->centre)
		return (free(cylinder), error("Error\nCylinder: invalid centre"),
			NULL);
	cylinder->axis = atoxyz(input[1]);
	if (!cylinder->axis || !is_normalised(*cylinder->axis))
		return (free_cylinder(cylinder),
			error("Error\nCylinder: invalid axis"), NULL);
	if (info_count == 5)
		return (cylinder->material = (t_material){0}, cylinder);
	if (!is_valid_material(input + 5))
		return (free_cylinder(cylinder), error("Error\nCylinder: \
			invalid shininess"), NULL);
	cylinder->material = create_material(input + 5);
	return (cylinder);
}
