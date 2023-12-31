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
