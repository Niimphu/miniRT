/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:00:45 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/13 16:23:44 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../lib/miniRT.h"
# include "../free/free.h"
# include "../colour/colour.h"
# include "../maths/xyz.h"

int			new_element(char *line, t_scene *scene);
void		add_shape(t_scene *scene, void *shape, int type);
void		add_cone(t_scene *scene, void *cone);
void		add_triangle(t_scene *scene, void *triangle);
t_material	create_material(char **input);

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
int			new_cone(char **input, t_scene *scene);
int			new_triangle(char **input, t_scene *scene);

#endif
