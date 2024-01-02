/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/02 18:11:50 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "../printer/printer.h" //debug

#define END 1

static int	parse_by_line(int fd, t_rt *rt);

int	parse(char *filename, t_rt *rt)
{
	int	fd;

	fd = open_file(filename);
	if (fd == FAIL || parse_by_line(fd, rt) == FAIL)
		return (close(fd), FAIL);
	close(fd);
	if (!rt->scene->camera)
		return (ft_perror("Error\nScene: missing camera"), FAIL);
	if (!rt->scene->light && !rt->scene->ambience)
		return (ft_perror("Error\nScene: missing lighting"), FAIL);
	if (!rt->scene->spheres && !rt->scene->planes && !rt->scene->cylinders)
		return (ft_perror("Error\nScene: missing objects"), FAIL);
	print_scene_info(rt->scene);
	return (OK);
}

static int	parse_by_line(int fd, t_rt *rt)
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
	return (OK);
}
