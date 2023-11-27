/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 22:13:21 by yiwong            #+#    #+#             */
/*   Updated: 2022/12/17 21:08:22 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*r;

	i = 0;
	r = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			r = ((char *)s + i);
		i++;
	}
	if (s[i] == (char)c)
		r = ((char *)s + i);
	return (r);
}
