/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 18:32:13 by yiwong            #+#    #+#             */
/*   Updated: 2023/03/16 13:23:32 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This function is effectively the opposite of atoi(). It allocates memory and
	returns a string representing the integer received as an argument.*/

#include "libft.h"

char	*ft_itoa_gen(char *r, int n, int len, int sign)
{
	while (n)
	{
		r[--len] = (n % 10) + '0';
		n /= 10;
	}
	if (sign == -1)
		r[0] = '-';
	return (r);
}

int	ft_itoa_len(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	int		sign;
	int		len;
	char	*r;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = ft_itoa_len(n);
	r = malloc(sizeof(char) * (len + 1));
	if (!r)
		return (NULL);
	sign = 1;
	if (n < 0)
		sign = -1;
	n *= sign;
	ft_itoa_gen(r, n, len, sign);
	r[len] = '\0';
	return (r);
}
