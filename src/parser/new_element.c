/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_element.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 19:38:49 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/17 19:38:49 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../free/free.h"

static int	get_element_id(char *string);
static int	create_element(int id, char **raw_input, t_scene *scene);

int	new_element(char *line, t_scene *scene)
{
	int		id;
	int		status;
	char	**raw_input;

	if (!*line || is_empty(line))
		return (FAIL);
	raw_input = ft_split(line, ' ');
	if (!raw_input)
		return (FAIL);
	id = get_element_id(raw_input[0]);
	status = OK;
	if (id == FAIL || create_element(id, raw_input + 1, scene) == FAIL)
		status = FAIL;
	free_string_array(&raw_input);
	return (status);
}

static int	create_element(int id, char **raw_input, t_scene *scene)
{
	int	status;

	if (id == AMBIENCE)
		status = new_ambience(raw_input, scene);
	else if (id == CAMERA)
		status = new_camera(raw_input, scene);
	else if (id == LIGHT)
		status = new_light(raw_input, scene);
	else if (id == SPHERE)
		status = new_sphere(raw_input, scene);
	else if (id == PLANE)
		status = new_plane(raw_input, scene);
	else
		status = new_cylinder(raw_input, scene);
	return (status);
}

static int	get_element_id(char *string)
{
	if (!ft_strncmp(string, "A ", 2))
		return (AMBIENCE);
	if (!ft_strncmp(string, "C ", 2))
		return (CAMERA);
	if (!ft_strncmp(string, "L ", 2))
		return (LIGHT);
	if (!ft_strncmp(string, "sp ", 2))
		return (SPHERE);
	if (!ft_strncmp(string, "pl ", 2))
		return (PLANE);
	if (!ft_strncmp(string, "cy ", 2))
		return (CYLINDER);
	ft_perror("error: valid identifier not found");
	return (FAIL);
}
