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

#include "../../lib/miniRT.h"

int	parse(char *filename, t_scene *scene)
{
	int	fd;

	fd = open_file(filename);
	if (fd == FAIL)
		return (FAIL);
	(void)scene;
	close(fd);
	return (0);
}
