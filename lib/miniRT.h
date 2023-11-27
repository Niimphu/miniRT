#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "mlx_linux/mlx.h"

# include <fcntl.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <X11/keysymdef.h>

typedef struct s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

int	initialise(char *file, t_vars *mlx_data);
int	raytrace(t_vars *mlx_data);
int	key_pressed(int keycode, t_vars *mlx_data);
int	window_closed(t_vars *mlx_data);
void	quit(t_vars *mlx_data);

#endif