/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <droslyn@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/17 23:50:15 by droslyn           #+#    #+#             */
/*   Updated: 2021/03/18 19:49:08 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_error(char *str_err)
{
	size_t	len;

	len = ft_strlen(str_err);
	write(2, str_err, len);
	exit(1);
}
