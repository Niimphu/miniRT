/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/15 17:38:19 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "mlx_linux/mlx.h"

# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <X11/keysymdef.h>

# define FAIL -1

typedef struct s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_scene {

}				t_scene;

void	initialise(t_vars *mlx_data);
int		raytrace(t_vars *mlx_data);

int		parse(char *filename);
int		open_file(char *filename);

int		key_pressed(int keycode, t_vars *mlx_data);
int		window_closed(t_vars *mlx_data);
void	quit(t_vars *mlx_data);

#endif