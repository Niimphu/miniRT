/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:00:45 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/23 18:32:09 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../lib/miniRT.h"
# include "../free/free.h"
# include "../colour/colour.h"
# include "../maths/xyz.h"

int			new_element(char *line, t_scene *scene);

bool		is_empty(const char *string);
bool		ft_isint(const char *str);
bool		ft_isdouble(const char *str);
bool		is_valid_material(char **raw_material);
bool		is_valid_rgb(t_rgb colour);

char		*trim_nl(char *str);

double		ft_atod(const char *str);
t_rgb		atorgb(char *string);
t_xyz		*atoxyz(char *string);

int			new_ambience(char **input, t_scene *scene);
int			new_camera(char **input, t_scene *scene);
int			new_light(char **input, t_scene *scene);
int			new_sphere(char **input, t_scene *scene);
int			new_plane(char **input, t_scene *scene);
int			new_cylinder(char **input, t_scene *scene);

#endif
