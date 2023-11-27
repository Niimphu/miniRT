/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 23:34:35 by yiwong            #+#    #+#             */
/*   Updated: 2022/12/26 23:34:35 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		slen;
	char	*src;
	char	*dst;

	src = (char *)s;
	slen = ft_strlen(src);
	dst = malloc(sizeof(char) * (slen + 1));
	if (!dst)
		return (NULL);
	ft_memcpy(dst, src, slen);
	dst[slen] = '\0';
	return (dst);
}
