/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/15 17:51:10 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

#define END 1

static int	read_file(int fd, t_rt *rt);

int	parse(char *filename, t_rt *rt)
{
	int	fd;

	fd = open_file(filename);
	if (fd == FAIL || read_file(fd, rt) == FAIL)
		return (close(fd), FAIL);
	close(fd);
	return (0);
}

static int	read_file(int fd, t_rt *rt)
{
	char	*line;
	int		status;

	status = OK;
	while (status == OK)
	{
		line = get_next_line(fd);
		if (!line)
			status = END;
		else if (!is_empty(line) && new_element(line, rt->scene) == FAIL)
			status = FAIL;
		free(line);
	}
	if (status == FAIL)
		return (FAIL);
	return (0);
}
