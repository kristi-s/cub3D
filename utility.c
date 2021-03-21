/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <droslyn@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:29:54 by droslyn           #+#    #+#             */
/*   Updated: 2021/03/21 18:52:31 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

void			ft_check_extension(char *line, char *ext)
{
	size_t		len_ext;
	size_t		i;

	i = ft_strlen(line);
	len_ext = ft_strlen(ext);
	while (ft_isspace(line[i - 1]) && i > len_ext)
		i--;
	while ((i > len_ext) && (len_ext > 0) && (line[i - 1] == ext[len_ext - 1]))
	{
		i--;
		len_ext--;
	}
	if (len_ext > 0)
		ft_error("Error map: extension isn't correct\n");
}

void			ft_parse_resolution(char *line, t_map *info)
{
	int			i;
	int			n;

	i = 0;
	while (ft_isspace(line[i]) || ft_isdigit(line[i]))
		i++;
	if (line[i] != '\0')
		ft_error("Error map: string with 'R' has not valid simbols or '-'\n");
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	n = i;
	while (ft_isdigit(line[i]))
		i++;
	if (i - n < 10)
		info->w = ft_atoi(line);
	while (ft_isspace(line[i]))
		i++;
	n = i;
	if (i - n < 10)
		info->h = ft_atoi(&line[n]);
}
