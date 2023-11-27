#include "../lib/miniRT.h"

// int	set_vars(t_vars *vars);
int	create_window(t_vars *mlx_data);

int	initialise(char *file, t_vars *mlx_data)
{
	(void)file;
	mlx_data->mlx = mlx_init();
	create_window(mlx_data);
	return (0);
}

int	create_window(t_vars *mlx_data)
{
	const int	x = 1280;
	const int	y = 720;

	mlx_data->win = mlx_new_window(mlx_data->mlx, x, y, "Ray.");
	return (0);
}

// int	new_map(t_vars *vars)
// {
// 	int	fd;

// 	if (!vars->name)
// 		vars->name = "default";
// 	if (vars->map)
// 		free_ppointer(vars->map);
// 	fd = open_map_file(vars->name);
// 	if (fd < 0)
// 		return (FAIL);
// 	vars->map = read_map(fd, vars->name);
// 	close(fd);
// 	if (!vars->map)
// 		error_exit(FAIL);
// 	set_vars(vars);
// 	return (OK);
// }

// int	set_vars(t_vars *vars)
// {
// 	locate_first(vars->map, 'E', vars->exit_coords);
// 	get_map_size(vars->map, vars->map_size);
// 	count_collectibles(vars);
// 	vars->frame = 0;
// 	return (0);
// }

