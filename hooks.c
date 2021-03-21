/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <droslyn@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:52:44 by droslyn           #+#    #+#             */
/*   Updated: 2021/03/18 21:54:33 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int				ft_close(void)
{
	exit(0);
}

static void		ft_key_change(int keycode, char status, int key[6][2])
{
	int i;

	i = 0;
	if (keycode == KEY_ESC)
	{
		exit(0);
	}
	while (i < 6)
	{
		if (keycode == key[i][1])
		{
			key[i][0] = status;
			return ;
		}
		i++;
	}
}

int				ft_key_press(int keycode, t_map *info)
{
	ft_key_change(keycode, 1, info->key);
	return (0);
}

int				ft_key_release(int keycode, t_map *info)
{
	ft_key_change(keycode, 0, info->key);
	return (0);
}
