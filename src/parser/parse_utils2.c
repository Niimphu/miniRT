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

bool	is_valid_float(const char *str)
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

float	atof(char *str)
{
	float	result;
	float	factor;
	int		sign;
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
		result = result * 10.0 + (str[i++] - '0');
	if (str[i++] != '.')
		return (sign * result);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result += (str[i++] - '0') * factor;
		factor *= 0.1;
	}
	return (sign * result);
}
