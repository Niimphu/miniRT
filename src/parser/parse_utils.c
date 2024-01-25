/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/17 14:15:19 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/17 14:15:19 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	is_empty(const char *string)
{
	int	i;

	i = 0;
	while (string[i])
	{
		if (string[i] != ' ' && string[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

bool	ft_isint(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	return (true);
}

bool	ft_isdouble(const char *str)
{
	int	i;
	int	digits;

	i = 0;
	digits = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
	{
		digits++;
		i++;
	}
	if (str[i] == '.')
	{
		i++;
		if (!ft_isdigit(str[i]))
			return (false);
		while (ft_isdigit(str[i]))
			i++;
	}
	return (digits > 0 && !str[i]);
}

bool	is_valid_material(char **raw_material)
{
	if (!ft_isdouble(raw_material[0]) || !ft_isint(raw_material[1]))
		return (false);
	if (ft_atod(raw_material[0]) < 0 || ft_atoi(raw_material[1]) < 1)
		return (false);
	return (true);
}

bool	is_valid_rgb(t_rgb colour)
{
	if (colour.r < 0 || colour.r > 255 || colour.g < 0 || colour.g > 255
		|| colour.b < 0 || colour.b > 255)
		return (false);
	return (true);
}
