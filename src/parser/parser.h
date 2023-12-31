/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:00:45 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/15 18:00:45 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../../lib/miniRT.h"

# define AMBIENCE 1
# define CAMERA 2
# define LIGHT 3
# define SPHERE 4
# define PLANE 5
# define CYLINDER 6

int		new_element(char *line, t_scene *scene);

bool			is_empty(const char *string);
bool			ft_isint(const char *str);
char			*trim_nl(char *str);

float			ft_atof(const char *str);
bool			ft_isfloat(const char *str);
unsigned int	*atorgb(char *string);
float			*atoxyz(char *string);

int				new_ambience(char **raw_input, t_scene *scene);
int				new_camera(char **raw_input, t_scene *scene);
int				new_light(char **raw_input, t_scene *scene);
int				new_sphere(char **raw_input, t_scene *scene);
int				new_plane(char **raw_input, t_scene *scene);
int				new_cylinder(char **raw_input, t_scene *scene);

#endif
