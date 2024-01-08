/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:15:40 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/08 15:15:40 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "colour.h"

bool	is_valid_rgb(t_rgb colour)
{
	if (colour.r < 0 || colour.r > 255 || colour.g < 0 || colour.g > 255
		|| colour.b < 0 || colour.b > 255)
		return (false);
	return (true);
}

int	rgb_to_hex(t_rgb *colour)
{
	return ((colour->r << 16) | (colour->g << 8) | colour->b);
}
