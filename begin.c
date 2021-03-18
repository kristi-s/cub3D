/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <droslyn@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 00:55:36 by droslyn           #+#    #+#             */
/*   Updated: 2021/03/19 00:21:56 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_cam	*ft_init_cam(unsigned int p_x, unsigned int p_y)
{
	t_cam		*camera;

	if (!(camera = malloc(sizeof(t_cam))))
		ft_error("Error memory allocation\n");
	camera->dir_x = 0;
	camera->dir_y = 0;
	camera->plane_x = 0;
	camera->plane_y = 0;
	camera->pos_x = p_x + 0.5;
	camera->pos_y = p_y + 0.5;
	return (camera);
}

t_cam			*ft_set_pos_player(unsigned int p_x, unsigned int p_y, \
														char way_player)
{
	t_cam		*camera;

	camera = ft_init_cam(p_x, p_y);
	if (way_player == 'N')
	{
		camera->dir_y = -1;
		camera->plane_x = FOV;
	}
	else if (way_player == 'S')
	{
		camera->dir_y = 1;
		camera->plane_x = -FOV;
	}
	else if (way_player == 'W')
	{
		camera->dir_x = -1;
		camera->plane_y = -FOV;
	}
	else if (way_player == 'E')
	{
		camera->dir_x = 1;
		camera->plane_y = FOV;
	}
	return (camera);
}

void			ft_calc(t_map *info, t_cam *cam, unsigned int i, int x)
{
	x = 0;
	ft_init_cam_other(cam);
	while (x < info->w)
	{
		ft_calc_param_ray(info->w, x, cam);
		ft_find_wall(cam, info, 0);
		ft_calc_perp_and_param_line(x, info->h, cam, info);
		ft_take_line_from_pic(x, cam, info);
		ft_draw_floor_ceiling(info, x, cam->draw_start, cam->draw_end);
		x++;
	}
	if (info->count_sprites > 0)
	{
		ft_find_dist_spr(info);
		i = 0;
		while (i < info->count_sprites)
		{
			ft_calc_spr(info, info->sprites, cam, info->spr_oder[i]);
			i++;
			if (info->sprites->draw_start_x >= info->sprites->draw_end_x)
				continue;
			ft_draw_spr(info, info->sprites, info->sp_img->width, \
												info->sp_img->height);
		}
	}
}

static int		ft_render_next(t_map *info)
{
	int			i;

	i = 0;
	while (i < 6 && info->key[i][0] == 0)
		i++;
	if (i == 6)
		return (0);
	mlx_do_sync(info->mlx);
	ft_choose_action(i, info);
	info->img = mlx_new_image(info->mlx, info->w, info->h);
	if (!info->img)
		ft_error("Error: create new image fail\n");
	info->addr = mlx_get_data_addr(info->img, &info->bits_per_pixel, \
		&info->line_length, &info->endian);
	ft_calc(info, info->cam, 0, 0);
	mlx_put_image_to_window(info->mlx, info->win, info->img, 0, 0);
	mlx_destroy_image(info->mlx, info->img);
	return (0);
}

void			ft_render(t_map *info)
{
	ft_calc(info, info->cam, 0, 0);
	mlx_put_image_to_window(info->mlx, info->win, info->img, 0, 0);
	mlx_destroy_image(info->mlx, info->img);
	mlx_loop_hook(info->mlx, ft_render_next, info);
	mlx_hook(info->win, KEYPRESS, KeyPressMask, ft_key_press, info);
	mlx_hook(info->win, KEYRELEASE, KeyReleaseMask, ft_key_release, info);
	mlx_hook(info->win, DestroyNotify, StructureNotifyMask, ft_close, info);
	mlx_loop(info->mlx);
}
