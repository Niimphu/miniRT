/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:29:29 by Kekuhne           #+#    #+#             */
/*   Updated: 2024/01/08 14:46:49 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATH_UTILS_H
# define MATH_UTILS_H

typedef struct s_vector 
{
	float x;
	float y;
	float z;
} t_vector;

float		ft_sqr(float n);
t_vector	*cpy_vector(t_vector *cpy);
void		set_vector_to(t_vector *set, float x, float y, float z);
void		set_vector_to_single(t_vector *set, float n);
float		vector_lenght(t_vector *vec);
float		vector_lenght_sqr(t_vector *vec);
float		vector_normalize(t_vector *vec);
t_vector	*vector_add(t_vector *v1, t_vector *v2);
t_vector	vector_add2(t_vector *v1, t_vector *v2);
t_vector	*vector_sub(t_vector *v1, t_vector *v2);
t_vector	vector_sub2(t_vector *v1, t_vector *v2);
t_vector	*vector_div(t_vector *v, float f);
t_vector	vector_div2(t_vector *v, float f);
t_vector	*vector_mul(t_vector *v, float f);
t_vector	vector_mul2(t_vector *v, float f);
t_vector	*new_vector(void);
float		dot(t_vector *v1, t_vector *v2);
void		free_vector(t_vector *del);
t_vector	*cross(t_vector *v1, t_vector *v2);
t_vector	*vector_mul(t_vector *v, float f);
#endif