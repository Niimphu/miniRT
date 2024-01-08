/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   element.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 18:36:55 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/08 14:08:39 by Kekuhne          ###   ########.fr       */
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
	float		focal_lenght;
	float		viewport_height;
	float		viewport_width;
	t_vector	viewport_u;
	t_vector	viewport_v;
	t_vector	viewport_upper_left;
	t_vector	center;
	t_vector	pixel00_loc;
	t_vector	pixel_delta_u;
	t_vector	pixel_delta_v;
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
