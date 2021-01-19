/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:35:07 by droslyn           #+#    #+#             */
/*   Updated: 2020/11/06 22:36:23 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*list;
	t_list	*tail_lst;

	if (!lst || !(*f))
		return (0);
	if (!(new_lst = ft_lstnew((*f)(lst->content))))
		return (0);
	list = new_lst;
	tail_lst = new_lst;
	lst = lst->next;
	while (lst)
	{
		if (!(new_lst = ft_lstnew((*f)(lst->content))))
		{
			ft_lstclear(&list, del);
			return (0);
		}
		ft_lstadd_back(&tail_lst, new_lst);
		tail_lst = new_lst;
		lst = lst->next;
	}
	return (list);
}
