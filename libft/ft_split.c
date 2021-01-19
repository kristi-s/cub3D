/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 15:41:41 by droslyn           #+#    #+#             */
/*   Updated: 2020/11/05 18:11:08 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_count_word(char const *str, char c)
{
	int			count;

	count = 0;
	while (*str)
	{
		while (*str == c && *str != '\0')
			str++;
		if (*str != c && *str != '\0')
		{
			count++;
			while (*str != c && *str != '\0')
				str++;
		}
	}
	return (count);
}

static char		*ft_word_copy(char const *str, char c)
{
	int			i;
	char		*ptr_word;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	if (!(ptr_word = malloc((i + 1) * sizeof(char))))
		return (0);
	i = 0;
	while (str[i] != '\0' && str[i] != c)
	{
		ptr_word[i] = str[i];
		i++;
	}
	ptr_word[i] = '\0';
	return (ptr_word);
}

static char		**ft_memfree(char **ptr_arr, int i)
{
	while (i >= 0)
	{
		free(ptr_arr[i]);
		i--;
	}
	free(ptr_arr);
	ptr_arr = 0;
	return (ptr_arr);
}

char			**ft_split(char const *s, char c)
{
	char		**ptr_arr;
	int			count_wd;
	int			i;

	if (!s)
		return (0);
	count_wd = ft_count_word(s, c);
	if (!(ptr_arr = malloc((count_wd + 1) * (sizeof(char*)))))
		return (0);
	ptr_arr[count_wd] = 0;
	i = 0;
	while (*s)
	{
		while (*s == c && *s != '\0')
			s++;
		if (*s != c && *s != '\0')
		{
			if (!(ptr_arr[i] = ft_word_copy(s, c)))
				return (ft_memfree(ptr_arr, i - 1));
			i++;
			while (*s != c && *s != '\0')
				s++;
		}
	}
	return (ptr_arr);
}
