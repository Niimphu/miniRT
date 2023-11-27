/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 03:11:17 by yiwong            #+#    #+#             */
/*   Updated: 2022/12/20 03:11:17 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*d;
	char	*s;

	if (src == dest)
		return (dest);
	d = (char *)dest;
	s = (char *)src;
	if (d < s)
	{
		ft_memcpy(dest, src, n);
		return (dest);
	}
	while (n--)
		d[n] = s[n];
	return (dest);
}
