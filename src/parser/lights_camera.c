/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 21:58:19 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/20 21:58:19 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	new_ambience(char **raw_input, t_scene *scene)
{
	t_ambience	*ambience;

	if (strarray_size(raw_input) != 2)
		return (ft_perror("error: ambient light: two sets of info required"),
			FAIL);
	scene->ambience = ft_calloc(1, sizeof(t_ambience));
	ambience = scene->ambience;
	if (!ambience)
		return (FAIL);
	ambience->colour = NULL;
	if (!ft_isfloat(raw_input[0]))
		return (ft_perror("error: ambient light: invalid lighting ratio"),
			FAIL);
	ambience->lighting = ft_atof(raw_input[0]);
	if (ambience->lighting < 0.0 || ambience->lighting > 1.0)
		return (ft_perror("error: ambient light: invalid lighting ratio"),
			FAIL);
	ambience->colour = atorgb(raw_input[1]);
	if (!ambience->colour)
		return (ft_perror("error: ambient light: invalid RGB format"), FAIL);
	return (OK);
}

int	new_camera(char **raw_input, t_scene *scene)
{
	t_camera	*camera;

	if (strarray_size(raw_input) != 3)
		return (ft_perror("error: camera: three sets of info required"), FAIL);
	scene->camera = ft_calloc(1, sizeof(t_camera));
	camera = scene->camera;
	if (!camera)
		return (FAIL);
	camera->orientation = NULL;
	camera->view_point = atoxyz(raw_input[0]);
	if (!camera->view_point)
		return (ft_perror("error: camera: invalid viewpoint"), FAIL);
	camera->orientation = atoxyz(raw_input[1]);
	if (!camera->orientation || !is_normalised(camera->orientation))
		return (ft_perror("error: camera: invalid orientation"), FAIL);
	if (!ft_isint(raw_input[2]))
		return (ft_perror("error: camera: invalid field of view"), FAIL);
	camera->fov = ft_atoi(raw_input[2]);
	if (camera->fov < 0 || camera->fov > 180)
		return (ft_perror("error: camera: invalid field of view angle"), FAIL);
	return (OK);
}

int	new_light(char **raw_input, t_scene *scene)
{
	t_light	*light;

	if (strarray_size(raw_input) != 3)
		return (ft_perror("error: light: three sets of info required"), FAIL);
	scene->light = ft_calloc(1, sizeof(t_light));
	light = scene->light;
	if (!light)
		return (FAIL);
	light->colour = NULL;
	light->point = atoxyz(raw_input[0]);
	if (!light->point)
		return (ft_perror("error: light: invalid light point"), FAIL);
	if (!ft_isfloat(raw_input[1]))
		return (ft_perror("error: light: invalid brightness"), FAIL);
	light->brightness = ft_atof(raw_input[1]);
	if (light->brightness < 0.0 || light->brightness > 1.0)
		return (ft_perror("error: light: invalid brightness"), FAIL);
	light->colour = atorgb(raw_input[2]);
	if (!light->colour)
		return (ft_perror("error: light: invalid RGB format"), FAIL);
	return (OK);
}
