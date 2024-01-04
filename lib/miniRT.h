/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/03 13:14:27 by Kekuhne          ###   ########.fr       */
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

# include "element.h"

# define OK 0
# define FAIL -1

# define R 0
# define G 1
# define B 2

# define X 0
# define Y 1
# define Z 2

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		win_x;
	int		win_y;
}				t_vars;

typedef struct s_scene
{
	t_ambience	*ambience;
	t_camera	*camera;
	t_light		*light;
	t_list		*spheres;
	t_list		*planes;
	t_list		*cylinders;
}				t_scene;

typedef struct s_rt
{
	t_vars	*mlx_data;
	t_scene	*scene;
}				t_rt;

int		parse(char *filename, t_rt *rt);
int		open_file(char *filename);

int		initialise(t_rt *rt);

int		raytrace(t_rt *rt);

int		key_pressed(int keycode, t_rt *rt);
int		window_closed(t_rt *rt);
void	quit(t_rt *rt);

void	ft_perror(char *message);

int		strarray_size(char **array);
void	set_fov_y(t_vars *mlx_data, t_camera *camera);

#endif
