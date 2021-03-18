/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_ceiling_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <droslyn@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 01:32:05 by droslyn           #+#    #+#             */
/*   Updated: 2021/03/19 01:55:19 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	if (ft_isdigit(line[i]))
	{
		while (ft_isdigit(line[i]))
			i++;
		i++;
		return (i);
	}
	else
	{
		i++;
		while (ft_isspace(line[i]))
			i++;
		if (ft_isdigit(line[i]))
			return (i);
		else
			ft_error("Error map: get color ceiling or floor\n");
	}
	return (0);
}

void			ft_get_color(char *line, t_map *info)
{
	int			i;
	int			red;
	int			green;
	int			blue;

	i = ft_get_ind(line);
	red = ft_atoi(&line[i]);
	i = i + ft_get_ind(&line[i]);
	green = ft_atoi(&line[i]);
	i = i + ft_get_ind(&line[i]);
	blue = ft_atoi(&line[i]);
	if (red < 0 || red > 255 || blue < 0 || blue > 255 || green < 0 || \
																green > 255)
		ft_error("Error map: RGB color not in range [0,255]\n");
	if (line[0] == 'F')
		info->floor_color = ft_create_trgb_color(0, red, green, blue);
	if (line[0] == 'C')
		info->ceiling_color = ft_create_trgb_color(0, red, green, blue);
}
