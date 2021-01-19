/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 18:04:51 by droslyn           #+#    #+#             */
/*   Updated: 2020/11/04 18:09:36 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *ptr;
	t_list *ptr_next;

	if (!lst || !(*del))
		return ;
	ptr = *lst;
	while (ptr)
	{
		ptr_next = ptr->next;
		(*del)(ptr->content);
		free(ptr);
		ptr = ptr_next;
	}
	*lst = 0;
}
