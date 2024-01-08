/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 17:07:03 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/01 17:08:41 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTER_H
# define PRINTER_H

# include "../../lib/miniRT.h"

void	print_scene_info(t_scene *scene);
void	print_colour_info(t_rgb colour);
void	print_coord_info(t_vector *vector);
void	print_vector_info(t_vector *vector);

#endif
