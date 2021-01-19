/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:51:20 by droslyn           #+#    #+#             */
/*   Updated: 2020/11/05 18:39:06 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*ptr;

	len = ft_strlen(s1);
	if (!(ptr = malloc((len + 1) * sizeof(char))))
		return (0);
	ptr = ft_memcpy(ptr, s1, len);
	ptr[len] = '\0';
	return (ptr);
}
