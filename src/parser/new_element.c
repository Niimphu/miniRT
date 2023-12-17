/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_element.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 19:38:49 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/17 19:38:49 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	identify_element(char *string);

int	new_element(char *line, t_rt *rt)
{
	int	i;
	int	id;

	i = skip_spaces(line);
	id = identify_element(line + i);
	if (id == FAIL)
		return (FAIL);
	(void)rt;
	return (0);
}

static int	identify_element(char *string)
{
	if (!ft_strncmp(string, "A ", 2))
		return (AMBIENCE);
	if (!ft_strncmp(string, "C ", 2))
		return (CAMERA);
	if (!ft_strncmp(string, "L ", 2))
		return (LIGHT);
	if (!ft_strncmp(string, "sp ", 2))
		return (SPHERE);
	if (!ft_strncmp(string, "pl ", 2))
		return (PLANE);
	if (!ft_strncmp(string, "cy ", 2))
		return (CYLINDER);
	ft_perror("error: valid identifier not found");
	return (FAIL);
}
