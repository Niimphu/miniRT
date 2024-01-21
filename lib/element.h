/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 14:17:55 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/21 16:29:03 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:36:55 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/12 16:57:55 by Kekuhne          ###   ########.fr       */
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
	t_xyz	*point;
	t_xyz	*norm;
	t_rgb	colour;
	t_material	material;
}				t_plane;

typedef struct s_cylinder
{
	t_xyz	*centre;
	t_xyz	*axis;
	double	diameter;
	double	height;
	t_rgb	colour;
	t_material	material;
}				t_cylinder;

#endif
