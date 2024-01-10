/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:15:40 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/09 20:32:41 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "colour.h"

t_rgb	rgb_scale(t_rgb colour, double factor)
{
	t_rgb	result;

	result.r = (int)(colour.r * factor);
	if (result.r < 0)
		result.r = 0;
	else if (result.r > 255)
		result.r = 255;
	result.g = (int)(colour.g * factor);
	if (result.g < 0)
		result.g = 0;
	else if (result.g > 255)
		result.g = 255;
	result.b = (int)(colour.b * factor);
	if (result.b < 0)
		result.b = 0;
	else if (result.b > 255)
		result.b = 255;
	return (result);
}

t_rgb	rgb_add(t_rgb colour1, t_rgb colour2)
{
	t_rgb	result;

	result.r = colour1.r + colour2.r;
	if (result.r < 0)
		result.r = 0;
	else if (result.r > 255)
		result.r = 255;
	result.g = colour1.g + colour2.g;
	if (result.g < 0)
		result.g = 0;
	else if (result.g > 255)
		result.g = 255;
	result.b = colour1.b + colour2.b;
	if (result.b < 0)
		result.b = 0;
	else if (result.b > 255)
		result.b = 255;
	return (result);
}

bool	is_valid_rgb(t_rgb colour)
{
	if (colour.r < 0 || colour.r > 255 || colour.g < 0 || colour.g > 255
		|| colour.b < 0 || colour.b > 255)
		return (false);
	return (true);
}

int	rgb_to_hex(t_rgb colour)
{
	return ((colour.r << 16) | (colour.g << 8) | colour.b);
}
