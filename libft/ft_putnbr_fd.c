/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 19:07:31 by droslyn           #+#    #+#             */
/*   Updated: 2020/11/06 22:28:59 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_size_num(unsigned int number, int n)
{
	int				i;

	i = 0;
	while (number != 0)
	{
		number = number / 10;
		i++;
	}
	if (n < 0)
		i++;
	return (i);
}

void				ft_putnbr_fd(int n, int fd)
{
	char			str[12];
	unsigned int	num;
	int				i;

	if (n == 0)
	{
		ft_putstr_fd("0", fd);
		return ;
	}
	if (n > 0)
		num = n;
	else
	{
		num = n * (-1);
		str[0] = '-';
	}
	i = ft_size_num(num, n);
	str[i] = '\0';
	while (num != 0)
	{
		i--;
		str[i] = num % 10 + '0';
		num = num / 10;
	}
	return (ft_putstr_fd(str, fd));
}
