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

static int	create_element(char *line, t_scene *scene);
static int	get_element_id(char *string);

int	new_element(char *line, t_scene *scene)
{
	int	i;

	i = skip_spaces(line);
	if (create_element(line + i, scene) == FAIL)
		return (FAIL);
	return (0);
}

static int	create_element(char *line, t_scene *scene)
{
	int	status;
	int	id;

	status = OK;
	id = get_element_id(line);
	if (id == AMBIENCE)
		status = new_ambience(line, scene);
	else if (id == CAMERA)
		status = new_camera(line, scene);
	else if (id == LIGHT)
		status = new_light(line, scene);
	else if (id == SPHERE)
		status = new_sphere(line, scene);
	else if (id == PLANE)
		status = new_plane(line, scene);
	else if (id == CYLINDER)
		status = new_cylinder(line, scene);
	else
		status = FAIL;
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
