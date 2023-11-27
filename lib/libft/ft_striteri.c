/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:47:37 by yiwong            #+#    #+#             */
/*   Updated: 2023/02/11 17:51:09 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*This function applies the function 'f' on each character of the string 's'
received as an argument. The characters are passed by address to 'f' 
for modification if necessary.*/

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[0])
	{
		(*f)(i, s++);
		i++;
	}
}
