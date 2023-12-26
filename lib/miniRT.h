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
}				t_vars;

typedef struct s_scene
{
	t_ambience	*a_light;
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

int	strarray_size(char **array);

#endif
