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

static t_rt	*new_rt(void);

int	main(int argc, char **argv)
{
	t_rt	*rt;

	if (argc != 2)
		return (ft_putstr_fd("usage: ./miniRT <path/map.rt>\n", 2), 1);
	rt = new_rt();
	if (!rt)
		return (FAIL);
	if (parse(argv[1], rt) == FAIL)
		return (free(rt), FAIL);
	initialise(rt);
	raytrace(rt);
	return (0);
}

static t_rt	*new_rt(void)
{
	t_rt	*rt;

	rt = ft_calloc(sizeof(t_rt), 1);
	if (!rt)
		return (NULL);
	rt->scene = NULL;
	rt->mlx_data = NULL;
	return (rt);
}
