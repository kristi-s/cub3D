/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 20:50:14 by droslyn           #+#    #+#             */
/*   Updated: 2020/11/13 20:19:27 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int				ft_memsearch(char *mem)
{
	if (!mem)
		return (0);
	while (*mem != '\0')
	{
		if (*mem == '\n')
			return (1);
		mem++;
	}
	return (0);
}

int				ft_free(char *mem1, char *mem2)
{
	if (mem1 != NULL)
		free(mem1);
	if (mem2 != NULL)
		free(mem2);
	return (-1);
}

size_t			ft_strlen(char *s)
{
	size_t		len;

	if (!s)
		return (0);
	len = 0;
	while (*s)
	{
		s++;
		len++;
	}
	return (len);
}

char			*ft_strjoin(char *s1, char *s2)
{
	size_t		len;
	char		*ptr_str;
	char		*str;

	if (!s1 && !s2)
		return (0);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(ptr_str = malloc((len + 1) * sizeof(char))))
		return (0);
	str = ptr_str;
	while (s1 && *s1)
	{
		*ptr_str = *s1;
		s1++;
		ptr_str++;
	}
	ft_free(s1 - (len - ft_strlen(s2)), 0);
	while (s2 && *s2)
	{
		*ptr_str = *s2;
		s2++;
		ptr_str++;
	}
	*ptr_str = '\0';
	return (str);
}
