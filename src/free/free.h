/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 19:22:07 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/15 19:22:07 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

#include "../../lib/miniRT.h"

void	free_rt(t_rt **rt);
void	free_string(char **string);
void	free_string_array(char ***array);

void	free_ambience(t_ambience **ambience);
void	free_camera(t_camera **camera);
void	free_light(t_light **light);

void	free_sphere(void *node);

#endif
