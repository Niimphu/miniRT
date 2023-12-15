/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:57:56 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/15 19:21:09 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"

static void	free_mlx(t_vars *mlx_data);
static void	free_scene(t_scene *scene);

void	free_rt(t_rt *rt)
{
	if (rt)
	{
		free_mlx(rt->mlx_data);
		free_scene(rt->scene);
		free(rt);
		rt = NULL;
	}
}

static void	free_mlx(t_vars *mlx_data)
{
	if (mlx_data && mlx_data->mlx)
		free(mlx_data->mlx);
	mlx_data->mlx = NULL;
	if (mlx_data != NULL)
		free(mlx_data);
	mlx_data = NULL;
}

static void	free_scene(t_scene *scene)
{
	if (scene)
		free(scene);
	scene = NULL;
}

void	free_string(char *string)
{
	if (string)
	{
		free(string);
		string = NULL;
	}
}
