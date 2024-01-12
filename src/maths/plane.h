/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:02:04 by Kekuhne           #+#    #+#             */
/*   Updated: 2024/01/12 16:57:35 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include "xyz.h"
# include "../../lib/element.h"

t_intersect	ray_intersect_plane(t_xyz *viewpoint, t_xyz ray, t_plane *plane);

#endif