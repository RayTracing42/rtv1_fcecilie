/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcecilie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/24 17:04:41 by fcecilie          #+#    #+#             */
/*   Updated: 2016/11/27 11:47:26 by fcecilie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new;
	t_list *first;

	if (!lst || !f)
		return (NULL);
	new = f(lst);
	first = new;
	first->next = new;
	lst = lst->next;
	new = new->next;
	while (lst != NULL)
	{
		new = f(lst);
		lst = lst->next;
		new = new->next;
	}
	return (first);
}
