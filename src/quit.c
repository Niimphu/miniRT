/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/03 16:38:22 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/miniRT.h"
#include "free/free.h"

int	window_closed(t_rt *rt)
{
	mlx_clear_window(rt->mlx_data->mlx, rt->mlx_data->win);
	quit(rt);
	return (0);
}

void	quit(t_rt *rt)
{
	mlx_loop_end(rt->mlx_data->mlx);
	mlx_destroy_display(rt->mlx_data->mlx);
	free_rt(&rt);
	exit(0);
}
