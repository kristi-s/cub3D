/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:49:05 by droslyn           #+#    #+#             */
/*   Updated: 2020/11/04 21:07:21 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (!dst && !src)
		return (0);
	if (dst < src)
		return (ft_memcpy(dst, src, len));
	else
	{
		while (len)
		{
			len--;
			*((char *)(dst + len)) = *((char *)(src + len));
		}
		return (dst);
	}
}
