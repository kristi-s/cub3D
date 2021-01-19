/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/31 21:54:57 by droslyn           #+#    #+#             */
/*   Updated: 2020/11/08 13:56:59 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	len_needle;

	if (*needle == '\0')
		return ((char *)haystack);
	len_needle = ft_strlen(needle);
	while ((*haystack != '\0') && (len_needle <= len))
	{
		if (*haystack == *needle && !(ft_strncmp(haystack, needle, len_needle)))
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (0);
}
