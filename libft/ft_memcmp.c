/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:04:24 by droslyn           #+#    #+#             */
/*   Updated: 2020/11/04 17:45:19 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ptr_s1;
	unsigned char	*ptr_s2;

	ptr_s1 = (unsigned char	*)s1;
	ptr_s2 = (unsigned char *)s2;
	i = 0;
	while ((i < n) && (*(ptr_s1 + i) == *(ptr_s2 + i)))
		i++;
	if (i < n)
		return (*(ptr_s1 + i) - *(ptr_s2 + i));
	else
		return (0);
}
