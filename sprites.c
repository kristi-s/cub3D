/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <droslyn@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 01:11:46 by droslyn           #+#    #+#             */
/*   Updated: 2021/03/19 00:56:06 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void				ft_count_sprite(t_map *info)
{
	unsigned int	i;
	int				ind;

	i = 0;
	ind = 0;
	if (!(info->arr_sp = malloc(info->count_sprites * sizeof(int))))
		ft_error("Error memory allocation\n");
	if (!(info->spr_dist = malloc(info->count_sprites * sizeof(double))))
		ft_error("Error memory allocation\n");
	if (!(info->spr_oder = malloc(info->count_sprites * sizeof(int))))
		ft_error("Error memory allocation\n");
	if (!(info->sprites = malloc(sizeof(t_sprt))))
		ft_error("Error memory allocation\n");
	while (i < (info->max_line_len * info->count_line))
	{
		if (info->arr_map[i] == '2')
		{
			info->arr_sp[ind] = i;
			ind++;
		}
		i++;
	}
	if (!(info->z_buff = malloc(info->w * sizeof(double))))
		ft_error("Error memory allocation\n");
}

void				ft_sort(t_map *info)
{
	unsigned int	i;
	unsigned int	j;
	double			tmp;
	int				temp_i;

	j = 0;
	while (j < info->count_sprites - 1)
	{
		i = 0;
		while (i < info->count_sprites - j - 1)
		{
			if (info->spr_dist[i] < info->spr_dist[i + 1])
			{
				tmp = info->spr_dist[i];
				info->spr_dist[i] = info->spr_dist[i + 1];
				info->spr_dist[i + 1] = tmp;
				temp_i = info->spr_oder[i];
				info->spr_oder[i] = info->spr_oder[i + 1];
				info->spr_oder[i + 1] = temp_i;
			}
			i++;
		}
		j++;
	}
}

void				ft_find_dist_spr(t_map *info)
{
	unsigned int	i;
	double			spr_x;
	double			spr_y;

	i = 0;
	while (i < info->count_sprites)
	{
		info->spr_oder[i] = i;
		spr_x = (double)(info->arr_sp[i] % info->max_line_len) + 0.5;
		spr_y = (double)(info->arr_sp[i] / info->max_line_len) + 0.5;
		info->spr_dist[i] = (pow((info->cam->pos_x - spr_x), 2) + \
								pow((info->cam->pos_y - spr_y), 2));
		i++;
	}
	ft_sort(info);
}

void				ft_calc_spr(t_map *info, t_sprt *spr, t_cam *cm, int ind)
{
	spr->x = (double)(info->arr_sp[ind] % info->max_line_len) + 0.5 - \
																cm->pos_x;
	spr->y = (double)(info->arr_sp[ind] / info->max_line_len) + 0.5 - \
																cm->pos_y;
	spr->inv_det = 1.0 / (cm->plane_x * cm->dir_y - cm->dir_x * cm->plane_y);
	spr->transform_x = spr->inv_det * (cm->dir_y * spr->x - \
										cm->dir_x * spr->y);
	spr->transform_y = spr->inv_det * (-cm->plane_y * spr->x + \
														cm->plane_x * spr->y);
	spr->sprite_screen_x = (int)((info->w / 2) * \
							(1 + spr->transform_x / spr->transform_y));
	spr->sprite_height = abs((int)(info->h / (spr->transform_y)));
	spr->draw_start_y = -spr->sprite_height / 2 + info->h / 2;
	if (spr->draw_start_y < 0)
		spr->draw_start_y = 0;
	spr->draw_end_y = spr->sprite_height / 2 + info->h / 2;
	if (spr->draw_end_y >= info->h)
		spr->draw_end_y = info->h - 1;
	spr->sprite_width = abs((int)(info->h / (spr->transform_y)));
	spr->draw_start_x = -spr->sprite_width / 2 + spr->sprite_screen_x;
	if (spr->draw_start_x < 0)
		spr->draw_start_x = 0;
	spr->draw_end_x = spr->sprite_width / 2 + spr->sprite_screen_x;
	if (spr->draw_end_x >= info->w)
		spr->draw_end_x = info->w - 1;
}

void				ft_draw_spr(t_map *info, t_sprt *spr, int txt_w, int txt_h)
{
	int				x;
	int				y;

	x = spr->draw_start_x;
	while (x < spr->draw_end_x)
	{
		spr->txtr_x = (int)(256 * (x - (-spr->sprite_width / 2 + \
					spr->sprite_screen_x)) * txt_w / spr->sprite_width) / 256;
		if (spr->transform_y > 0 && x > 0 && x < info->w && \
				spr->transform_y < info->z_buff[x])
		{
			y = spr->draw_start_y;
			while (y < spr->draw_end_y)
			{
				spr->d = (y) * 256 - info->h * 128 + spr->sprite_height * 128;
				spr->txtr_y = ((spr->d * txt_h) / spr->sprite_height) / 256;
				spr->color = ft_get_pxl_clr(info->sp_img, spr->txtr_x, \
																spr->txtr_y);
				if ((spr->color & 0x00FFFFFF) != 0)
					ft_my_mlx_pixel_put(info, x, y, spr->color);
				y++;
			}
		}
		x++;
	}
}
