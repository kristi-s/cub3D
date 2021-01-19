/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:52:58 by droslyn           #+#    #+#             */
/*   Updated: 2020/11/06 20:33:16 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len_src;

	if (!dst || !src)
		return (0);
	len_src = ft_strlen(src);
	if (dstsize != 0)
	{
		while (dstsize > 1 && *src != '\0')
		{
			*dst = *src;
			dstsize--;
			dst++;
			src++;
		}
		*dst = '\0';
	}
	return (len_src);
}
