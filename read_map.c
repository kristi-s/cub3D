/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <droslyn@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:37:55 by droslyn           #+#    #+#             */
/*   Updated: 2021/03/19 02:02:30 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			ft_check_resolution(char *line, t_map *info)
{
	int			x;
	int			y;

	if (info->w != 0)
		ft_error("Error map: init resolution twice\n");
	ft_parse_resolution(line, info);
	mlx_get_screen_size(info->mlx, &x, &y);
	if ((info->w <= 0) || (info->h <= 0) ||
			(info->flag_save == 0 && (info->w > x || info->h > y)))
	{
		info->w = x;
		info->h = y;
	}
	info->mlx = mlx_init();
	info->win = mlx_new_window(info->mlx, info->w, info->h, info->file);
	info->img = mlx_new_image(info->mlx, info->w, info->h);
	info->addr = mlx_get_data_addr(info->img, &info->bits_per_pixel, \
									&info->line_length, &info->endian);
}

static int		ft_is_space_line(char *line)
{
	int			i;

	i = 0;
	if (!line)
		ft_error("Error map: file reading error");
	if (line[0] == '\0')
		return (-1);
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '\0')
		return (-1);
	else
		return (i);
}

void			ft_parse_line(char *line, t_map *info)
{
	int			i;
	static int	flag_split;

	if ((i = ft_is_space_line(line)) == -1)
	{
		if (info->start_row != NULL)
			flag_split = 1;
		free(line);
		return ;
	}
	if (line[i] == 'R')
		ft_check_resolution(&line[i + 1], info);
	else if (line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || \
														line[i] == 'E')
		ft_check_texture(&line[i], info, 1);
	else if (line[i] == 'F' || line[i] == 'C')
		ft_get_color(&line[i], info);
	else
	{
		if (flag_split == 1)
			ft_error("Error map: map is split\n");
		ft_copy_map(line, info);
	}
	if (line != NULL)
		free(line);
}

void			ft_init_info(t_map *info, int i)
{
	i = 0;
	while (i < 8)
		info->key[i++][0] = 0;
	info->key[0][1] = KEY_A;
	info->key[1][1] = KEY_S;
	info->key[2][1] = KEY_D;
	info->key[3][1] = KEY_W;
	info->key[4][1] = KEY_LEFT;
	info->key[5][1] = KEY_RIGTH;
	info->w = 0;
	info->h = 0;
	info->north_txtr = NULL;
	info->south_txtr = NULL;
	info->west_txtr = NULL;
	info->east_txtr = NULL;
	info->sprite_txtr = NULL;
	info->floor_color = NOCOLOR;
	info->ceiling_color = NOCOLOR;
	info->count_line = 0;
	info->max_line_len = 0;
	info->count_sprites = 0;
	info->start_row = NULL;
	info->last_row = NULL;
	info->pos_pl = 0;
	info->arr_map = NULL;
}

void			ft_read_map(t_map *info)
{
	int			fd;
	int			n;
	char		*line;

	if ((fd = open(info->file, 0)) == -1)
		ft_error("Error map: file opening error");
	while ((n = ft_read_line(fd, &line)) > 0)
		ft_parse_line(line, info);
	if (n == 0)
	{
		ft_parse_line(line, info);
		ft_create_arr_map(info);
		ft_paint_texture(info);
		if (info->flag_save == 1)
			ft_make_screenshot(info);
		ft_render(info);
	}
	if (n == -1)
		ft_error("Error map: file reading error");
	if (close(fd) == -1)
		ft_error("Error map: file closing error");
}
