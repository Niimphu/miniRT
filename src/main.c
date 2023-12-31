/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/12 18:01:52 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/miniRT.h"
#include "free/free.h"

static t_rt	*new_rt(void);

int	main(int argc, char **argv)
{
	t_rt	*rt;

	if (argc != 2)
		return (ft_perror("usage: ./miniRT <path/map.rt>"), 1);
	rt = new_rt();
	if (!rt)
		return (FAIL);
	if (parse(argv[1], rt) == FAIL)
		return (free(rt), FAIL);
	initialise(rt);
	raytrace(rt);
	free_rt(&rt);
	return (0);
}

static t_rt	*new_rt(void)
{
	t_rt	*rt;

	rt = ft_calloc(1, sizeof(t_rt));
	if (!rt)
		return (NULL);
	rt->scene = ft_calloc(1, sizeof(t_scene));
	if (!rt->scene)
		return (NULL);
	rt->scene->ambience = NULL;
	rt->scene->camera = NULL;
	rt->scene->light = NULL;
	rt->scene->spheres = NULL;
	rt->scene->planes = NULL;
	rt->scene->cylinders = NULL;
	rt->mlx_data = NULL;
	return (rt);
}
