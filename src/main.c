#include "../lib/miniRT.h"

int	main(int argc, char **argv)
{
	t_vars	*mlx_data;

	if (argc != 2)
		return (ft_putstr_fd("usage: ./miniRT <path/map.rt>\n", 2), 1);
	(void)argv;
	if (parse(argv[1]) == FAIL)
		return (1);
	mlx_data = ft_calloc(sizeof(t_vars), 1);
	initialise(mlx_data);
	raytrace(mlx_data);
	return (0);
}
