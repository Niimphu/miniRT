/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 19:27:15 by yiwong            #+#    #+#             */
/*   Updated: 2022/12/22 19:27:15 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	char	*s;
	size_t	slen;
	size_t	i;

	slen = ft_strlen(src);
	if (!size || size == 0)
		return (slen);
	s = (char *)src;
	i = 0;
	while (s[i] && i < size)
	{
		dst[i] = s[i];
		i++;
	}
	if (size <= slen)
		dst[size - 1] = '\0';
	else if (size != 0)
		dst[i] = '\0';
	return (slen);
}
