/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msaa_colour.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 18:15:53 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/15 18:26:24 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "colour.h"
#include "msaa.h"

t_rgb	hex_to_rgb(int hex_colour)
{
	t_rgb	result;

	result.r = (hex_colour >> 16) & 0xFF;
	result.g = (hex_colour >> 8) & 0xFF;
	result.b = hex_colour & 0xFF;
	return (result);
}

t_rgb	average_4colour(t_rgb a, t_rgb b, t_rgb c, t_rgb d)
{
	t_rgb	result;

	result.r = (a.r + b.r + c.r + d.r) / 4;
	result.g = (a.g + b.g + c.g + d.g) / 4;
	result.b = (a.b + b.b + c.b + d.b) / 4;
	return (result);
}
