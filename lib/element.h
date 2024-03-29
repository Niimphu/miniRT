/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:36:55 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/13 18:05:38 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMENT_H
# define ELEMENT_H

# include "material.h"
# include "../src/colour/colour.h"
# include "../src/maths/xyz.h"

typedef struct s_ambience
{
	double	lighting;
	t_rgb	colour;
}				t_ambience;

typedef struct s_camera
{
	t_xyz	*position;
	t_xyz	*forward;
	int		fov;
	t_xyz	right;
	t_xyz	up;
}				t_camera;

typedef struct s_light
{
	t_xyz	*point;
	double	brightness;
	t_rgb	colour;
}				t_light;

typedef struct s_sphere
{
	t_xyz		*centre;
	double		diameter;
	t_rgb		colour;
	t_material	material;
}				t_sphere;

typedef struct s_plane
{
	t_xyz		*point;
	t_xyz		*norm;
	t_rgb		colour;
	t_material	material;
}				t_plane;

typedef struct s_cylinder
{
	t_xyz		*centre;
	t_xyz		*axis;
	double		radius;
	double		height;
	t_rgb		colour;
	t_material	material;
}				t_cylinder;

typedef struct s_cone
{
	t_xyz		*centre;
	t_xyz		*axis;
	double		radius;
	double		height;
	double		theta;
	t_rgb		colour;
	t_material	material;
}				t_cone;

typedef struct s_triangle
{
	t_xyz		*a;
	t_xyz		*b;
	t_xyz		*c;
	t_rgb		colour;
	t_material	material;
}				t_triangle;

#endif
