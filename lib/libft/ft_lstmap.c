/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yiwong <yiwong@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/25 01:49:04 by yiwong            #+#    #+#             */
/*   Updated: 2023/01/25 01:49:04 by yiwong           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*r;
	t_list	*current;

	if (!lst || !f || !del)
		return (NULL);
	current = ft_lstnew((*f)(lst->content));
	r = current;
	lst = lst->next;
	while (lst)
	{
		current->next = ft_lstnew((*f)(lst->content));
		if (!r->next)
		{
			ft_lstdelone(r, del);
			return (NULL);
		}
		current = current->next;
		lst = lst->next;
	}
	return (r);
}
