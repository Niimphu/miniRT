/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:22:07 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/05 17:02:17 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "../../lib/miniRT.h"

void	free_rt(t_rt **rt);
void	free_string(char **string);
void	free_string_array(char ***array);

void	free_ambience(t_ambience **ambience);
void	free_camera(t_camera **camera);
void	free_light(void *node);

void	free_sphere(void *node);
void	free_plane(void *node);
void	free_cylinder(void *node);
void	free_cone(void *node);

#endif
