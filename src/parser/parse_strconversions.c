/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/26 14:23:03 by yiwong            #+#    #+#             */
/*   Updated: 2023/12/26 14:23:03 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_rgb	*atorgb(char *string)
{
	t_rgb	*rgb;
	char	**str_rgb;

	str_rgb = ft_split(string, ',');
	if (!str_rgb)
		return (NULL);
	if (strarray_size(str_rgb) != 3 || !ft_isint(str_rgb[R])
		|| !ft_isint(str_rgb[G]) || !ft_isint(str_rgb[B]))
		return (free_string_array(&str_rgb),
				ft_perror("error: ambient light: invalid RGB format"), NULL);
	rgb = ft_calloc(3, sizeof(unsigned int));
	if (!rgb)
		return (free_string_array(&str_rgb), NULL);
	rgb->r = ft_atoi(str_rgb[R]);
	rgb->g = ft_atoi(str_rgb[G]);
	rgb->b = ft_atoi(str_rgb[B]);
	free_string_array(&str_rgb);
	if (rgb->r < 0 || rgb->r > 255 || rgb->g < 0 || rgb->g > 255
		|| rgb->b < 0 || rgb->b > 255)
		return (ft_perror("error: ambient light: invalid RGB values"),
				free(rgb), NULL);
	return (rgb);
}

t_vector	*atoxyz(char *string)
{
	t_vector	*xyz;
	char		**str_xyz;

	str_xyz = ft_split(string, ',');
	if (!str_xyz)
		return (NULL);
	if (strarray_size(str_xyz) != 3 || !ft_isfloat(str_xyz[R])
		|| !ft_isfloat(str_xyz[G]) || !ft_isfloat(str_xyz[B]))
		return (free_string_array(&str_xyz),
				ft_perror("error: ambient light: invalid vector format"), NULL);
	xyz = ft_calloc(3, sizeof(float));
	if (!xyz)
		return (free_string_array(&str_xyz), NULL);
	xyz->x = ft_atof(str_xyz[X]);
	xyz->y = ft_atof(str_xyz[Y]);
	xyz->z = ft_atof(str_xyz[Z]);
	free_string_array(&str_xyz);
	return (xyz);
}

float	ft_atof(const char *str)
{
	float	result;
	float	factor;
	float	sign;
	int		i;

	i = 0;
	result = 0.0f;
	factor = 0.1f;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
		result = result * 10.0f + ((float)(str[i++]) - '0');
	if (str[i++] != '.')
		return (sign * result);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result += ((float)(str[i++]) - '0') * factor;
		factor *= 0.1f;
	}
	return (sign * result);
}
