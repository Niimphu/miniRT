/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:25:42 by yiwong            #+#    #+#             */
/*   Updated: 2023/05/21 18:49:24 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This function applies the function 'f' to each character in string 's'. It
	passes its i as the first argument to allocate and return a new
	string that results from successive applications of 'f'.*/

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*r;

	r = ft_strdup(s);
	if (!r)
		return (NULL);
	i = 0;
	while (s[i])
	{
		r[i] = (*f)(i, (char)s[i]);
		i++;
	}
	return (r);
}
