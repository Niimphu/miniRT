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

bool	is_valid_rgb(t_rgb colour);
int		rgb_to_hex(t_rgb *colour);

#endif
