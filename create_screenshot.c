/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_screenshot.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <droslyn@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 00:45:46 by droslyn           #+#    #+#             */
/*   Updated: 2021/03/18 21:25:37 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void			ft_bmp_header_init(unsigned char *buf, t_map *info)
{
	unsigned int	size;

	size = info->w * info->h + ALLBMPHEADER;
	buf[0] = (unsigned char)'B';
	buf[1] = (unsigned char)'M';
	buf[2] = size;
	buf[3] = size >> 8;
	buf[4] = size >> 16;
	buf[5] = size >> 24;
	buf[10] = ALLBMPHEADER;
	buf[14] = BITMAPINFO_SIZE;
	buf[18] = info->w;
	buf[19] = info->w >> 8;
	buf[20] = info->w >> 16;
	buf[21] = info->w >> 24;
	buf[22] = info->h;
	buf[23] = info->h >> 8;
	buf[24] = info->h >> 16;
	buf[25] = info->h >> 24;
	buf[26] = 1;
	buf[28] = info->bits_per_pixel;
}

static void			ft_create_bmp(t_map *info)
{
	int				fd;
	int				i;
	int				j;
	unsigned char	buf[ALLBMPHEADER];

	bzero(buf, 54);
	ft_bmp_header_init(buf, info);
	if ((fd = open(FILE_BMP, O_CREAT | O_RDWR | O_TRUNC, PMOD)) == -1)
		ft_error("Error create bmp file: fd = -1\n");
	write(fd, buf, ALLBMPHEADER);
	i = info->h - 1;
	j = (info->bits_per_pixel / 8) * info->w;
	while (i >= 0)
	{
		write(fd, &info->addr[i * info->line_length], j);
		i--;
	}
	close(fd);
}

void				ft_make_screenshot(t_map *info)
{
	ft_calc(info, info->cam, 0, 0);
	ft_create_bmp(info);
	mlx_destroy_image(info->mlx, info->img);
	exit(0);
}
