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
#include "../free/free.h"

unsigned int	*atorgb(char *string)
{
	unsigned int	*rgb;
	char			**str_rgb;

	str_rgb = ft_split(string, ',');
	if (!str_rgb)
		return (NULL);
	if (strarray_size(str_rgb) != 3 || !ft_isint(str_rgb[R])
		|| !ft_isint(str_rgb[G]) || !ft_isint(str_rgb[B]))
		return (free_string_array(&str_rgb),
			ft_perror("error: ambient light: invalid RGB format"), NULL);
	rgb = ft_calloc(sizeof(float), 3);
	if (!rgb)
		return (free_string_array(&str_rgb), NULL);
	rgb[R] = ft_atoi(str_rgb[R]);
	rgb[G] = ft_atoi(str_rgb[G]);
	rgb[B] = ft_atoi(str_rgb[B]);
	free_string_array(&str_rgb);
	if (rgb[R] < 0 || rgb[R] > 255 || rgb[G] < 0 || rgb[G] > 255
		|| rgb[B] < 0 || rgb[B] > 255)
		return (ft_perror("error: ambient light: invalid RGB values"),
			free(rgb), NULL);
	return (rgb);
}

//lighting range [0.0, 1.0]
//RGB range      [0-255]
int	new_ambience(char **raw_input, t_scene *scene)
{
	t_ambience	*ambience;

	if (strarray_size(raw_input) != 2)
		return (FAIL);
	scene->a_light = ft_calloc(sizeof(t_ambience), 1);
	ambience = scene->a_light;
	if (!ambience)
		return (FAIL);
	if (!is_valid_float(raw_input[0]))
		return (ft_perror("error: ambient light: invalid float"), FAIL);
	ambience->lighting = ft_atof(raw_input[0]);
	if (ambience->lighting < 0.0 || ambience->lighting > 1.0)
		return (ft_perror("error: ambient light: invalid lighting ratio"),
			FAIL);
	ambience->colour = atorgb(raw_input[2]);
	if (!ambience->colour)
		return (ft_perror("error: ambient light: invalid RGB format"), FAIL);
	return (OK);
}

int	new_camera(char **raw_input, t_scene *scene)
{
	(void)raw_input;
	(void)scene;
	return (OK);
}

int	new_light(char **raw_input, t_scene *scene)
{
	(void)raw_input;
	(void)scene;
	return (OK);
}
