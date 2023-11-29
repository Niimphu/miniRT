#include "../../lib/miniRT.h"

static bool	is_filename_valid(char *filename);
static bool	ends_with_rt(char *filename);

int	open_file(char *filename)
{
	int		fd;

	if (!is_filename_valid(filename))
		return (FAIL);
	fd = open(filename, O_RDONLY);
	if (fd == FAIL)
		ft_putstr_fd("error: file could not be opened\n", 2);
	return (fd);
}

static bool	is_filename_valid(char *filename)
{
	if (ft_strchr(filename, '.') && !ends_with_rt(filename))
	{
		ft_putstr_fd("error: map must be of .rt format\n", 2);
		return (false);
	}
	return (true);
}

static bool	ends_with_rt(char *filename)
{
	int	i;

	i = ft_strlen(filename - 3);
	if (!ft_strncmp(filename + i, ".rt", 4))
		return (true);
	return (false);
}
