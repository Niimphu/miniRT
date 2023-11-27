/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 17:49:57 by yiwong            #+#    #+#             */
/*   Updated: 2023/02/11 17:45:14 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This function allocates and returns a copy of the string 's1', with any
	consecutive characters in any combination specified in 'set' removed
	from the beginning and the end of the string.*/

#include "libft.h"

int	ft_strtrim_check(char s, char *set)
{
	int	i;

	if (!set)
		return (0);
	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	char	*r;

	if (!(*s1))
		return (ft_strdup(""));
	i = 0;
	while (ft_strtrim_check(s1[i], (char *)set) && s1[i])
		i++;
	if (!s1[i])
		return (ft_strdup(""));
	j = ft_strlen(s1) - 1;
	while (ft_strtrim_check(s1[j], (char *)set) && j)
		j--;
	r = ft_substr(s1, i, j - i + 1);
	if (!r)
		return (NULL);
	return (r);
}
