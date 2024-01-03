/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/03 16:38:22 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/miniRT.h"

int	key_pressed(int keycode, t_rt *rt)
{
	if (keycode == XK_Escape)
	{
		mlx_clear_window(rt->mlx_data->mlx, rt->mlx_data->win);
		mlx_destroy_window(rt->mlx_data->mlx, rt->mlx_data->win);
		quit(rt);
	}
	return (0);
}
