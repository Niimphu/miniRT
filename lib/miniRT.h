/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/23 16:03:19 by yiwong           ###   ########.fr       */
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

# ifndef B
#  define R 0
#  define G 1
#  define B 2
# endif

# define X 0
# define Y 1
# define Z 2

# define AMBIENCE 1
# define CAMERA 2
# define LIGHT 3
# define SPHERE 4
# define PLANE 5
# define CYLINDER 6

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	int		win_x;
	int		win_y;
	double	aspect_ratio;
}				t_vars;

typedef struct s_scene
{
	t_ambience	*ambience;
	t_camera	*camera;
	t_list		*lights;
	t_list		*spheres;
	t_list		*planes;
	t_list		*cylinders;
}				t_scene;

typedef struct s_rt
{
	t_vars	*mlx_data;
	t_scene	*scene;
	bool	msaa;
}				t_rt;

int		parse(int argc, char **argv, t_rt *rt);
int		open_file(char *filename);

int		initialise(t_rt *rt);

int		raytrace(t_rt *rt);

int		key_pressed(int keycode, t_rt *rt);
int		window_closed(t_rt *rt);
void	quit(t_rt *rt);

int		error(char *message);

int		strarray_size(char **array);

#endif
