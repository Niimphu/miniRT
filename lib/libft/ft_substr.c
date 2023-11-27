/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:29:43 by yiwong            #+#    #+#             */
/*   Updated: 2023/01/04 20:29:43 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* This function allocates and returns a substring from the string 's',
	define by the i 'start' and the maximum size 'len'.*/

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*r;
	char	*str;
	size_t	subslen;

	if ((size_t)start >= ft_strlen(s))
		return (ft_strdup(""));
	subslen = ft_strlen(s + start);
	if (len > subslen)
		len = subslen;
	r = malloc(sizeof(char) * (len + 1));
	if (!r)
	{
		free(r);
		r = NULL;
		return (NULL);
	}
	str = (char *)s;
	while (start--)
		str++;
	ft_memcpy(r, str, len);
	r[len] = '\0';
	return (r);
}
