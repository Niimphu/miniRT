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
		return (error("Error\nAmbient light: two sets of info required"));
	scene->ambience = ft_calloc(1, sizeof(t_ambience));
	ambience = scene->ambience;
	if (!ambience)
		return (FAIL);
	if (!ft_isdouble(raw_input[0]))
		return (error("Error\nAmbient light: invalid lighting ratio"));
	ambience->lighting = ft_atod(raw_input[0]);
	if (ambience->lighting < 0.0 || ambience->lighting > 1.0)
		return (error("Error\nAmbient light: invalid lighting ratio"));
	ambience->colour = atorgb(raw_input[1]);
	if (!is_valid_rgb(ambience->colour))
		return (error("Error\nAmbient light: invalid RGB format"));
	return (OK);
}

int	new_camera(char **raw_input, t_scene *scene)
{
	t_camera	*camera;

	if (strarray_size(raw_input) != 3)
		return (error("Error\nCamera: three sets of info required"));
	scene->camera = ft_calloc(1, sizeof(t_camera));
	camera = scene->camera;
	if (!camera)
		return (FAIL);
	camera->forward = NULL;
	camera->position = atoxyz(raw_input[0]);
	if (!camera->position)
		return (error("Error\nCamera: invalid viewpoint"));
	camera->forward = atoxyz(raw_input[1]);
	if (!camera->forward || !is_normalised(*camera->forward))
		return (error("Error\nCamera: invalid forward"));
	if (!ft_isint(raw_input[2]))
		return (error("Error\nCamera: invalid field of view"));
	camera->fov = ft_atoi(raw_input[2]);
	if (camera->fov < 0 || camera->fov > 180)
		return (error("Error\nCamera: invalid field of view angle"));
	return (OK);
}

int	new_light(char **raw_input, t_scene *scene)
{
	t_light	*light;

	if (strarray_size(raw_input) != 3)
		return (error("Error\nLight: three sets of info required"));
	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		return (FAIL);
	light->point = atoxyz(raw_input[0]);
	if (!light->point)
		return (error("Error\nLight: invalid light point"));
	if (!ft_isdouble(raw_input[1]))
		return (error("Error\nLight: invalid brightness"));
	light->brightness = ft_atod(raw_input[1]);
	if (light->brightness < 0.0 || light->brightness > 1.0)
		return (error("Error\nLight: invalid brightness"));
	light->colour = atorgb(raw_input[2]);
	if (!is_valid_rgb(light->colour))
		return (error("Error\nLight: invalid RGB format"));
	if (!scene->lights)
		scene->lights = ft_lstnew(light);
	else
		ft_lstadd_back(&scene->lights, ft_lstnew(light));
	return (OK);
}
