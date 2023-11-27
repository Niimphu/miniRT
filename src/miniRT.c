#include "../lib/miniRT.h"

int	raytrace(t_vars *mlx_data)
{
	mlx_hook(mlx_data->win, KeyPress, 1L << 0, key_pressed, mlx_data);
	mlx_hook(mlx_data->win, DestroyNotify, 0L, window_closed, mlx_data);
	// mlx_expose_hook(mlx_data->win, draw, mlx_data);
	mlx_loop(mlx_data->mlx);
	return (0);
}
