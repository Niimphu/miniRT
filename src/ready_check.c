#include "../lib/miniRT.h"

// int	arg_check(int argc, char **argv)
// {
// 	int	error_code;

// 	if (argc == 1)
// 		return (OK);
// 	else if (argc >= 3)
// 		return (ARGN);
// 	error_code = map_check(argv[argc - 1]);
// 	if (error_code != OK)
// 		return (error_code);
// 	return (OK);
// }

// int	map_check(char *name)
// {
// 	const int	fd = open_map_file(name);
// 	int			error_code;
// 	char		**map;

// 	error_code = OK;
// 	if (!fd)
// 		return (MAP_NAME);
// 	map = read_map(fd, name);
// 	if (!map)
// 		error_code = BAD_MAP;
// 	else
// 		error_code = validate_map(map);
// 	close(fd);
// 	free_ppointer(map);
// 	return (error_code);
// }
