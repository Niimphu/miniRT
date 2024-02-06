/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/02 17:59:59 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "mlx_linux/mlx.h"

# include <pthread.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <X11/keysymdef.h>

# include "element.h"

# define MAX_BOUNCES 5
# define TOLERANCE 1e-6

//C1 and C3 are coefficients for light intensity drop-off based on distance
# define C1 1.2
# define C3 0.00005

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

# ifndef BONUS

typedef struct s_rt
{
	t_vars	*mlx_data;
	t_scene	*scene;
	bool	msaa;
}				t_rt;

# else

typedef struct s_rt
{
	t_vars			*mlx_data;
	t_scene			*scene;
	bool			msaa;
	pthread_mutex_t	print_lock;
}				t_rt;

# endif

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
