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

bool	is_empty(char *string)
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

int	skip_spaces(char *string)
{
	int	i;

	i = 0;
	while (string[i] == ' ')
		i++;
	return (i);
}
