/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:36:55 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/15 18:36:55 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENT_H
# define ELEMENT_H

# include "../src/colour/colour.h"
# include "../src/math/math_utils.h"

typedef struct s_ambience
{
	float		lighting;
	t_rgb		*colour;
}				t_ambience;

typedef struct s_camera
{
	t_vector	*view_point;
	t_vector	*orientation;
	int			fov;
}				t_camera;

typedef struct s_light
{
	t_vector	*point;
	float		brightness;
	t_rgb		*colour;
}				t_light;

typedef struct s_sphere
{
	t_vector	*centre;
	float		diameter;
	t_rgb		*colour;
}				t_sphere;

typedef struct s_plane
{
	t_vector	*point;
	t_vector	*norm;
	t_rgb		*colour;
}				t_plane;

typedef struct s_cylinder
{
	t_vector	*centre;
	t_vector	*axis;
	float		diameter;
	float		height;
	t_rgb		*colour;
}				t_cylinder;

#endif
