/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <droslyn@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 01:32:05 by droslyn           #+#    #+#             */
/*   Updated: 2021/03/21 19:18:27 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		ft_create_trgb_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static int		ft_get_ind(char *line)
{
	int			i;

	if (!line)
		return (0);
	i = 0;
	while (ft_isspace(line[i]))
		i++;
	while (ft_isdigit(line[i]))
		i++;
	i++;
	return (i);
}

static void		ft_check_format(char *line, int i, int count)
{
	int			ind;

	i = 0;
	count = 0;
	ind = 1;
	while (i < 3)
	{
		while (ft_isspace(line[ind]))
			ind++;
		while (ft_isdigit(line[ind]))
		{
			ind++;
			count++;
		}
		if ((i < 2 && (count > 3 || count == 0 || line[ind] != ',')) || \
			(i == 2 && (count > 3 || count == 0)))
			ft_error("Error map: rgb incorrect\n");
		if ((++i) < 3)
			ind++;
		count = 0;
	}
	while (ft_isspace(line[ind]))
		ind++;
	if (line[ind] != '\0')
		ft_error("Error map: rgb incorrect\n");
}

void			ft_get_color(char *line, t_map *info)
{
	int			i;
	int			red;
	int			green;
	int			blue;

	ft_check_format(line, 0, 0);
	i = 1;
	red = ft_atoi(&line[i]);
	i = i + ft_get_ind(&line[i]);
	green = ft_atoi(&line[i]);
	i = i + ft_get_ind(&line[i]);
	blue = ft_atoi(&line[i]);
	if (red < 0 || red > 255 || blue < 0 || blue > 255 || green < 0 || \
																green > 255)
		ft_error("Error map: RGB color not in range [0,255]\n");
	if (line[0] == 'F' && info->floor_color == NOCOLOR)
		info->floor_color = ft_create_trgb_color(0, red, green, blue);
	else if (line[0] == 'C' && info->ceiling_color == NOCOLOR)
		info->ceiling_color = ft_create_trgb_color(0, red, green, blue);
	else
		ft_error("Error map: floor or ceiling color init twice\n");
}
