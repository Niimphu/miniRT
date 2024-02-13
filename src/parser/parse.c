/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Kekuhne <kekuehne@student.42wolfsburg.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:38:22 by yiwong            #+#    #+#             */
/*   Updated: 2024/02/05 16:51:02 by Kekuhne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "printer.h" //debug

#define END 1

static int	parse_by_line(int fd, t_rt *rt);
static int	check_flags(char *flag, t_rt *rt);

int	parse(int argc, char **argv, t_rt *rt)
{
	int	fd;
	int	i;

	i = 1;
	if (argc == 3)
	{
		if (check_flags(argv[i++], rt) == FAIL)
			return (FAIL);
	}
	fd = open_file(argv[i]);
	if (fd == FAIL || parse_by_line(fd, rt) == FAIL)
		return (close(fd), FAIL);
	close(fd);
	if (!rt->scene->camera)
		return (error("Error\nScene: missing camera"), FAIL);
	if (!rt->scene->lights)
		return (error("Error\nScene: missing lights"), FAIL);
	if (!rt->scene->spheres && !rt->scene->planes
			&& !rt->scene->cylinders && !rt->scene->cone)
		return (error("Error\nScene: missing objects"), FAIL);
	print_scene_info(rt->scene);
	return (OK);
}

static int	check_flags(char *flag, t_rt *rt)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(flag);
	if (!flag[i] || len != 2 || flag[i++] != '-')
		error("Error\nArguments: invalid flag");
	while (flag[i])
	{
		if (flag[i] == 'a')
			rt->msaa = true;
		else
		{
			error("Error\nValid flags: a");
			return (FAIL);
		}
		i++;
	}
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
