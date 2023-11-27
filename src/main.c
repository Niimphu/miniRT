#include "../lib/miniRT.h"

int	main(int argc, char **argv)
{
	// int		error_code;
	t_vars	*mlx_data;

	// error_code = arg_check(argc, argv);
	// if (error_code != OK)
	// 	error_exit(error_code);
	if (argc != 2)
		return (1);
	mlx_data = ft_calloc(sizeof(t_vars), 1);
	ft_memset(mlx_data, 0, sizeof(t_vars));
	initialise(argv[1], mlx_data);
	raytrace(mlx_data);
	return (0);
}
