/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_strconversions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:23:03 by yiwong            #+#    #+#             */
/*   Updated: 2024/01/10 14:00:05 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_rgb	atorgb(char *string)
{
	t_rgb	rgb;
	char	**str_rgb;

	str_rgb = ft_split(string, ',');
	if (!str_rgb)
		return ((t_rgb){-1, -1, -1});
	if (strarray_size(str_rgb) != 3 || !ft_isint(str_rgb[R])
		|| !ft_isint(str_rgb[G]) || !ft_isint(str_rgb[B]))
		return (free_string_array(&str_rgb), (t_rgb){-1, -1, -1});
	rgb.r = ft_atoi(str_rgb[R]);
	rgb.g = ft_atoi(str_rgb[G]);
	rgb.b = ft_atoi(str_rgb[B]);
	free_string_array(&str_rgb);
	return (rgb);
}

t_xyz	*atoxyz(char *string)
{
	t_xyz	*xyz;
	char	**str_xyz;

	str_xyz = ft_split(string, ',');
	if (!str_xyz)
		return (NULL);
	if (strarray_size(str_xyz) != 3 || !ft_isdouble(str_xyz[R])
		|| !ft_isdouble(str_xyz[G]) || !ft_isdouble(str_xyz[B]))
		return (free_string_array(&str_xyz), NULL);
	xyz = ft_calloc(3, sizeof(double));
	if (!xyz)
		return (free_string_array(&str_xyz), NULL);
	xyz->x = ft_atod(str_xyz[X]);
	xyz->y = ft_atod(str_xyz[Y]);
	xyz->z = ft_atod(str_xyz[Z]);
	free_string_array(&str_xyz);
	return (xyz);
}

double	ft_atod(const char *str)
{
	double	result;
	double	factor;
	double	sign;
	int		i;

	i = 0;
	result = 0.0;
	factor = 0.1;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10.0 + ((double)(str[i++]) - '0');
	if (str[i++] != '.')
		return (sign * result);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result += ((double)(str[i++]) - '0') * factor;
		factor *= 0.1;
	}
	return (sign * result);
}

char	*trim_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i + 1])
		i++;
	if (str[i] == '\n')
		str[i] = '\0';
	return (str);
}
