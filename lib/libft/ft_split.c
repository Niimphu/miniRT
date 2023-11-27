/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:32:04 by yiwong            #+#    #+#             */
/*   Updated: 2023/03/16 18:17:33 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This functions allocates and returns an array of strings obtained by
	splitting string 's' into substrings, using the character 'c' as a delimiter.
	The array must end with a NULL pointer.*/

#include "libft.h"

void	split_clear(char **r)
{
	int	i;

	i = 0;
	while (r[i])
	{
		free(r[i]);
		r[i++] = NULL;
	}
}

int	ft_splen(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

int	ft_split_count(char *s, char c)
{
	int	i;
	int	scount;

	i = 0;
	scount = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i ++;
		}
		else
		{
			while (s[i] != c && s[i])
				i ++;
			scount ++;
		}
	}
	return (scount);
}

char	**split_write(char *str, char c, char **r)
{
	int	count;
	int	scount;

	count = 0;
	scount = ft_split_count(str, c);
	while (count < scount)
	{
		if (str[0] != c)
		{
			r[count] = ft_substr(str, 0, ft_splen(str, c));
			if (!(r[count]))
			{
				split_clear(r);
				r = NULL;
				return (NULL);
			}
			str += ft_splen(str, c);
			count++;
		}
		str++;
	}
	return (r);
}

char	**ft_split(char const *s, char c)
{
	char	**r;
	char	*str;
	int		scount;

	str = (char *)s;
	scount = ft_split_count(str, c);
	r = (char **)malloc(sizeof(char *) * (scount + 1));
	if (!r)
	{
		free(r);
		r = NULL;
		return (NULL);
	}
	r[scount] = NULL;
	r = split_write(str, c, r);
	return (r);
}
