/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 21:30:16 by yiwong            #+#    #+#             */
/*   Updated: 2022/12/22 21:30:16 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi_extended(int i, char *s, int sign);

int	ft_atoi(const char *nptr)
{
	int		i;
	char	*s;
	int		sign;

	i = 0;
	s = (char *)nptr;
	while (s[i] == ' ' || s[i] == '\t'
		|| s[i] == '\n' || s[i] == '\r' || s[i] == '\f' || s[i] == '\v')
		i++;
	sign = 1;
	while (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign *= -1;
		i++;
	}
	return (ft_atoi_extended(i, s, sign));
}

int	ft_atoi_extended(int i, char *s, int sign)
{
	int	r;

	r = 0;
	if (ft_isdigit(s[i]))
	{
		r = (s[i] - '0') * sign;
		i++;
	}
	while (ft_isdigit(s[i]))
	{
		r = 10 * r + (s[i] - '0') * sign;
		i++;
	}
	return (r);
}
