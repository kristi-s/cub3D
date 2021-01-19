/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 17:56:11 by droslyn           #+#    #+#             */
/*   Updated: 2020/11/06 20:32:38 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	size;
	char	*ptr_str;
	char	*str;

	if (!s1 || !set)
		return (0);
	while (*s1 != '\0' && ft_strchr(set, (int)*s1))
		s1++;
	size = ft_strlen(s1);
	if (size != 0)
	{
		while (ft_strchr(set, (int)*(s1 + size - 1)))
			size--;
	}
	if (!(str = malloc((size + 1) * sizeof(char))))
		return (0);
	ptr_str = str;
	while (size--)
	{
		*str = *s1;
		str++;
		s1++;
	}
	*str = '\0';
	return (ptr_str);
}
