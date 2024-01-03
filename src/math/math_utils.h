/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 17:29:29 by Kekuhne           #+#    #+#             */
/*   Updated: 2024/01/03 19:54:40 by Kekuhne          ###   ########.fr       */
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

float	ft_sqr(float n);
void	set_vector_to(t_vector *set, float x, float y, float z);
void	set_vector_to_single(t_vector *set, float n);
float	vector_lenght(t_vector *vec);
float	vector_normalize(t_vector *vec);
#endif