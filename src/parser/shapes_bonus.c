/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 15:18:35 by Kekuhne           #+#    #+#             */
/*   Updated: 2024/02/15 18:23:11 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "material.h"

static t_cone	*cone_extended(char **input, t_cone *cone,
					size_t info_count);

int	new_cone(char **input, t_scene *scene)
{
	t_cone		*cone;
	size_t		info_count;

	info_count = strarray_size(input);
	if (info_count != 5 && info_count != 8)
		return (error("Error\nCone: invalid parameter count"));
	cone = ft_calloc(1, sizeof(t_cone));
	if (!cone)
		return (FAIL);
	if (!ft_isdouble(input[2]) || ft_atod(input[2]) < 0.0f)
		return (free(cone), error("Error\ncone: \
			invalid diameter"));
	cone->radius = ft_atod(input[2]);
	if (!ft_isdouble(input[3]) || ft_atod(input[3]) < 0.0f)
		return (free(cone), error("Error\ncone: invalid height"));
	cone->height = ft_atod(input[3]);
	cone->colour = atorgb(input[4]);
	cone->theta = pow(cone->radius / cone->height, 2);
	if (!is_valid_rgb(cone->colour))
		return (free(cone), error("Error\ncone: invalid colour"));
	cone = cone_extended(input, cone, info_count);
	if (!cone)
		return (FAIL);
	return (add_cone(scene, cone), OK);
}

static t_cone	*cone_extended(char **input, t_cone *cone,
							size_t info_count)
{
	cone->axis = NULL;
	cone->centre = atoxyz(input[0]);
	if (!cone->centre)
		return (free(cone), error("Error\ncone: invalid centre"),
			NULL);
	cone->axis = atoxyz(input[1]);
	if (!cone->axis || !is_normalised(*cone->axis))
		return (free_cone(cone),
			error("Error\nCone: invalid axis"), NULL);
	if (info_count == 5)
		return (cone->material = (t_material){0}, cone);
	if (!is_valid_material(input + 5))
		return (free_cone(cone), error("Error\nCone: \
			invalid material"), NULL);
	cone->material = create_material(input + 5);
	return (cone);
}

int	new_triangle(char **input, t_scene *scene)
{
	t_triangle	*triangle;
	size_t		info_count;

	info_count = strarray_size(input);
	if (info_count != 4 && info_count != 7)
		return (error("Error\nTriangle: invalid parameter count"));
	triangle = ft_calloc(1, sizeof(t_triangle));
	if (!triangle)
		return (FAIL);
	triangle->a = atoxyz(input[0]);
	triangle->b = atoxyz(input[1]);
	triangle->c = atoxyz(input[2]);
	if (!triangle->a || !triangle->b || !triangle->c)
		return (free_triangle(triangle),
			error("Error\nTriangle: invalid points"));
	triangle->colour = atorgb(input[3]);
	if (!is_valid_rgb(triangle->colour))
		return (free(triangle), error("Error\nTriangle: invalid colour"));
	if (info_count == 4)
		return (triangle->material = (t_material){0},
				add_triangle(scene, triangle), OK);
	if (!is_valid_material(input + 4))
		return (free_triangle(triangle),
			error("Error\nTriangle: invalid material"));
	triangle->material = create_material(input + 4);
	return (add_triangle(scene, triangle), OK);
}
