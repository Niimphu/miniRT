/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:57:56 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/23 18:08:47 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

static void	free_mlx(t_vars **mlx_data);
static void	free_scene(t_scene **scene);

void	free_rt(t_rt **rt)
{
	if (*rt)
	{
		free_mlx(&((*rt)->mlx_data));
		free_scene(&((*rt)->scene));
		free(*rt);
		*rt = NULL;
	}
}

static void	free_mlx(t_vars **mlx_data)
{
	if ((*mlx_data) && (*mlx_data)->mlx)
		free((*mlx_data)->mlx);
	(*mlx_data)->mlx = NULL;
	if (*mlx_data != NULL)
		free(*mlx_data);
	mlx_data = NULL;
}

static void	free_scene(t_scene **scene)
{
	if (*scene)
	{
		if ((*scene)->ambience)
			free_ambience(&((*scene)->ambience));
		if ((*scene)->camera)
			free_camera(&((*scene)->camera));
		if ((*scene)->lights)
			ft_lstclear(&(*scene)->lights, free_light);
		if ((*scene)->spheres)
			ft_lstclear(&(*scene)->spheres, free_sphere);
		if ((*scene)->planes)
			ft_lstclear(&(*scene)->planes, free_plane);
		if ((*scene)->cylinders)
			ft_lstclear(&(*scene)->cylinders, free_cylinder);
		free(*scene);
	}
	scene = NULL;
}

void	free_string(char **string)
{
	if (*string)
	{
		free(*string);
		string = NULL;
	}
}

void	free_string_array(char ***array)
{
	int	i;

	i = 0;
	while ((*array)[i] != NULL)
	{
		free_string(&(*array)[i]);
		i++;
	}
	free(*array);
	*array = NULL;
}
