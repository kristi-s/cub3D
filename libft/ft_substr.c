/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 16:03:02 by droslyn           #+#    #+#             */
/*   Updated: 2020/11/06 20:53:32 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr_substr;
	char	*str;
	char	*sub;
	size_t	len_str;

	if (!s)
		return (0);
	if (start > ft_strlen(s))
		start = ft_strlen(s);
	str = (char *)s + start;
	len_str = ft_strlen(str);
	if (len < len_str)
		len_str = len;
	if (!(ptr_substr = malloc((len_str + 1) * sizeof(char))))
		return (0);
	sub = ptr_substr;
	while (len_str)
	{
		*ptr_substr = *str;
		ptr_substr++;
		str++;
		len_str--;
	}
	*ptr_substr = '\0';
	return (sub);
}
