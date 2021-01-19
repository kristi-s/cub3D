/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:56:15 by droslyn           #+#    #+#             */
/*   Updated: 2020/11/05 19:07:05 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;
	char	*ptr_c;

	len = ft_strlen(s);
	if (c == '\0')
		return ((char *)(s + len));
	if (len == 0)
		return (0);
	ptr_c = 0;
	while (*s != '\0')
	{
		if (*s == c)
			ptr_c = (char *)s;
		s++;
	}
	return (ptr_c);
}
