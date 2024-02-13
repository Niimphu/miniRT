/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 18:52:47 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/04 15:28:04 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS_H
# define BONUS_H

# include "../../lib/miniRT.h"
# include <pthread.h>
# define THREADS 12

typedef struct s_thread_info
{
	t_vars		*mlx;
	t_camera	*camera;
	t_rt		*rt;
	int			start_y;
	int			end_y;
}				t_thread_info;

t_thread_info	*create_threaddata(t_rt *rt, int start, int end);
int				start(int i, t_rt *rt);
int				end(int i, t_rt *rt);

#endif
