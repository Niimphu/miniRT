/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/23 16:03:19 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	is_filename_valid(char *filename);
static bool	file_exists(char *filename);

int	open_file(char *filename)
{
	int		fd;

	if (!file_exists(filename))
		return (FAIL);
	if (!is_filename_valid(filename))
		return (FAIL);
	fd = open(filename, O_RDONLY);
	if (fd == FAIL)
		error("Error\nFile could not be opened");
	return (fd);
}

static bool	is_filename_valid(char *filename)
{
	size_t	i;

	i = ft_strlen(filename) - 3;
	if (ft_strncmp(filename + i, ".rt", 4))
	{
		error("Error\nMap must be of .rt format");
		return (false);
	}
	return (true);
}

static bool	file_exists(char *filename)
{
	if (access(filename, F_OK) != 0)
	{
		error("Error\nFile not found");
		return (false);
	}
	return (true);
}
