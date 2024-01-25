/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 15:31:46 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/23 15:31:46 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERSECT_H
# define INTERSECT_H

# include "miniRT.h"
# include "xyz.h"

typedef struct s_intersect
{
	bool		valid;
	t_xyz		point;
	t_rgb		colour;
	double		distance;
	void		*shape;
	int			type;
	t_material	material;
}				t_intersect;

t_intersect	new_intersect(void);

#endif
