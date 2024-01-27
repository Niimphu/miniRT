/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colour.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 19:34:43 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/03 13:58:38 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOUR_H
# define COLOUR_H

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
}				t_rgb;

int		rgb_to_hex(t_rgb colour);
t_rgb	hex_to_rgb(int hex_colour);
t_rgb	rgb_scale(t_rgb colour, double factor);
t_rgb	rgb_add(t_rgb colour1, t_rgb colour2);
t_rgb	rgb_product(t_rgb base, t_rgb light);

#endif
