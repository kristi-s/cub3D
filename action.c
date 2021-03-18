/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <droslyn@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 01:09:02 by droslyn           #+#    #+#             */
/*   Updated: 2021/03/18 22:28:54 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void		ft_move(t_cam *cam, char *arr_map, unsigned int size, int way)
{
	t_move		tmp;

	tmp.dir = 1;
	if (way == KEY_S || way == KEY_A)
		tmp.dir = -1;
	if (way == KEY_S || way == KEY_W)
	{
		tmp.delta_x = cam->dir_x * MOVE_SPEED;
		tmp.delta_y = cam->dir_y * MOVE_SPEED;
	}
	else
	{
		tmp.delta_x = cam->plane_x * MOVE_SPEED;
		tmp.delta_y = cam->plane_y * MOVE_SPEED;
	}
	tmp.new_x = cam->pos_x + (tmp.dir * tmp.delta_x);
	tmp.new_y = cam->pos_y + (tmp.dir * tmp.delta_y);
	if (arr_map[(int)(tmp.new_x) + ((int)(tmp.new_y) * size)] != '1')
	{
		cam->pos_x = tmp.new_x;
		cam->pos_y = tmp.new_y;
	}
}

static void		ft_turn(t_cam *cam, int way)
{
	double		cur_dir_x;
	double		cur_plane_x;
	int			dir;
	double		delta_sin;
	double		delta_cos;

	dir = 1;
	if (way == KEY_LEFT)
		dir = -1;
	cur_dir_x = cam->dir_x;
	cur_plane_x = cam->plane_x;
	delta_sin = sin(dir * ROTATION);
	delta_cos = cos(dir * ROTATION);
	cam->dir_x = cam->dir_x * delta_cos - cam->dir_y * delta_sin;
	cam->dir_y = cur_dir_x * delta_sin + cam->dir_y * delta_cos;
	cam->plane_x = cam->plane_x * delta_cos - cam->plane_y * delta_sin;
	cam->plane_y = cur_plane_x * delta_sin + cam->plane_y * delta_cos;
}

void			ft_choose_action(int i, t_map *info)
{
	while (i < 6)
	{
		if (info->key[i][0] == 1)
		{
			if (i <= 3)
				ft_move(info->cam, info->arr_map, info->max_line_len, \
															info->key[i][1]);
			else
				ft_turn(info->cam, info->key[i][1]);
		}
		i++;
	}
}
