#include "../lib/miniRT.h"

int	window_closed(t_vars *mlx_data)
{
	mlx_clear_window(mlx_data->mlx, mlx_data->win);
	quit(mlx_data);
	return (0);
}

void	quit(t_vars *mlx_data)
{
	mlx_loop_end(mlx_data->mlx);
	mlx_destroy_display(mlx_data->mlx);
	free(mlx_data->mlx);
	exit(0);
}
