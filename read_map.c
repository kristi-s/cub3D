/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <droslyn@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:37:55 by droslyn           #+#    #+#             */
/*   Updated: 2021/03/18 19:38:23 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int			ft_append_buf(char **line, char *buf)
{
	char	*tmp;
	int		i;

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
		if (ft_append_buf(line,buf) == -1)
			return (-1);
	}
	if (n < 0)
		return (-1);
	return (0);
}

void		ft_check_resolution(char *line, t_map *info)
{
	int 	i;
	int		x;
	int		y;

	i = 0;
	info->w = ft_atoi(line);
	while (ft_isspace(line[i]))
		i++;
	while (ft_isdigit(line[i]))
		i++;
	info->h = ft_atoi(&line[i]);
	mlx_get_screen_size(info->mlx, &x, &y);
	if ((info->w <= 0) || (info->h <= 0) ||
		(info->w > x) || (info->h > y))
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

static int		ft_create_trgb_color(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

static int	ft_get_ind(char *line)
{
	int		i;

	if (!line)
		return 0;
	i = 0;
	if (ft_isdigit(line[i]))
	{
		while (ft_isdigit(line[i]))
			i++;
		i++;
		return i;
	}
	else
	{
		i++;
		while (ft_isspace(line[i]))
			i++;
		if (ft_isdigit(line[i]))
			return i;
		else
			ft_error("Error map: get color ceiling or floor\n");
	}
	return 0;
}

void		ft_get_color(char *line, t_map *info)
{
	int		i;
	int		red;
	int		green;
	int		blue;

	i = ft_get_ind(line);
	red = ft_atoi(&line[i]);
	i = i + ft_get_ind(&line[i]);
	green = ft_atoi(&line[i]);
	i = i + ft_get_ind(&line[i]);
	blue = ft_atoi(&line[i]);
	if (red < 0 || red > 255 || blue < 0 || blue > 255 || green < 0 || green > 255)
		ft_error("Error map: RGB color not in range [0,255]\n");
	if (line[0] == 'F')
		info->floor_color = ft_create_trgb_color(0, red, green, blue);
	if (line[0] == 'C')
		info->ceiling_color = ft_create_trgb_color(0, red, green, blue);
}

static char		**ft_switch_txtr(char *line, t_map *info)
{
	if (ft_strlen(line) < 5)
		ft_error("Error map: error texture\n");
	if ((line[0] == 'N' && line[1] == 'O' && info->north_txtr != NULL) ||
		(line[0] == 'S' && line[1] == 'O' && info->south_txtr != NULL) ||
		(line[0] == 'W' && line[1] == 'E' && info->west_txtr != NULL) ||
		(line[0] == 'E' && line[1] == 'A' && info->east_txtr != NULL) ||
		(line[0] == 'S' && line[1] == ' ' && info->sprite_txtr != NULL))
		ft_error("Error map: reinitialization texture\n");
	if (line[0] == 'N' && line[1] == 'O')
		return (&info->north_txtr);
	else if (line[0] == 'S' && line[1] == 'O')
		return (&info->south_txtr);
	else if (line[0] == 'W' && line[1] == 'E')
		return (&info->west_txtr);
	else if (line[0] == 'E' && line[1] == 'A')
		return (&info->east_txtr);
	else if (line[0] == 'S' && line[1] == ' ')
		return (&info->sprite_txtr);
	else
		ft_error("Error map: error texture\n");
	return 0;
}

void		ft_check_texture(char *line, t_map *info)
{
	int		i;
	int		len;
	char	*ptr;
	char	**adr;

	adr = ft_switch_txtr(line, info);
	i = 1;
	if (line[i] != ' ')
		i++;
	while (ft_isspace(line[i]))
		i++;
	len = 0;
	while (line[i] >= 33 && line[i] <= 126) {
		len++;
		i++;
	}
	if (!(ptr = malloc(len + 1)))
		ft_error("Error memory allocation\n");
	if (len == 0)
		ft_error("Error map: error texture\n");
	ptr[len] = '\0';
	i--;
	while (len-- > 0)
		ptr[len] = line[i--];
	*adr = ptr;
}

static int	ft_is_space_line(char *line)
{
	int		i;

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

void	ft_parse_line(char *line, t_map *info)
{
	int		i;
	static int flag_split;

	if ((i = ft_is_space_line(line)) == -1)
	{
		if (info->start_row != NULL)
			flag_split = 1;
		free(line);
		return;
	}
	if (line[i] == 'R')
		ft_check_resolution(&line[i + 1], info);
	else if(line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
		ft_check_texture(&line[i], info);
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

void	ft_init_info(t_map	*info)
{
	int	i;

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
	info->floor_color = 0;
	info->ceiling_color = 0;
	info->count_line = 0;
	info->max_line_len = 0;
	info->count_sprites = 0;
	info->start_row = NULL;
	info->last_row = NULL;
	info->pos_pl = 0;
	info->arr_map = NULL;
}

void		ft_read_map(t_map *info)
{
	int		fd;
	int		n;
	char	*line;

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


