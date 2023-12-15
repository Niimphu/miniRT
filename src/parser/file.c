/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/15 17:38:19 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/miniRT.h"

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
		ft_putstr_fd("error: file could not be opened\n", 2);
	return (fd);
}

static bool	is_filename_valid(char *filename)
{
	size_t	i;

	i = ft_strlen(filename - 4);
	if (ft_strncmp(filename + i, ".rt", 4))
	{
		ft_putstr_fd("error: map must be of .rt format\n", 2);
		return (false);
	}
	return (true);
}

static bool	file_exists(char *filename)
{
	if (access(filename, F_OK) != 0)
	{
		ft_putstr_fd("error: file not found\n", 2);
		return (false);
	}
	return (true);
}
