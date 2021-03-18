/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <droslyn@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:29:54 by droslyn           #+#    #+#             */
/*   Updated: 2021/03/19 01:56:47 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int		ft_append_buf(char **line, char *buf)
{
	char		*tmp;
	int			i;

	i = 0;
	if (!(tmp = malloc(ft_strlen(*line) + 2)))
		return (-1);
	while ((*line)[i])
	{
		tmp[i] = (*line)[i];
		i++;
	}
	tmp[i] = buf[0];
	tmp[i + 1] = '\0';
	free(*line);
	*line = tmp;
	return (1);
}

int				ft_read_line(int fd, char **line)
{
	static char	buf[2];
	int			n;

	if (fd < 0 || !line || !(*line = malloc(1)))
		return (-1);
	(*line)[0] = '\0';
	while ((n = read(fd, buf, 1)) > 0)
	{
		if (buf[0] == '\n')
			return (1);
		if (ft_append_buf(line, buf) == -1)
			return (-1);
	}
	if (n < 0)
		return (-1);
	return (0);
}

void			ft_my_mlx_pixel_put(t_map *info, int x, int y, int color)
{
	char		*dst;

	dst = info->addr + (y * info->line_length + x * (info->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
