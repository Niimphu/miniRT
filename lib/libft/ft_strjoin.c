/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 18:53:03 by yiwong            #+#    #+#             */
/*   Updated: 2023/02/11 17:43:52 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This string allocates and returns a new string, which is the result of the
	cocatenation of input strings 's1' and 's2'.*/

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	size_t	slen1;
	size_t	slen2;

	if (!s1 && !s2)
		return (ft_strdup(""));
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	slen1 = ft_strlen(s1);
	slen2 = ft_strlen(s2);
	r = malloc(sizeof(char) * (slen1 + slen2 + 1));
	if (!r)
		return (NULL);
	ft_strlcpy(r, s1, slen1 + 1);
	ft_strlcat(r + slen1, s2, slen2 + 1);
	return (r);
}
