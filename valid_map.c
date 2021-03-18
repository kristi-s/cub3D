/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <droslyn@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 01:15:02 by droslyn           #+#    #+#             */
/*   Updated: 2021/03/18 01:15:36 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void			ft_isvalid_first_line(int i, t_map *info)
{
	if (info->arr_map[i] != '1' && !(info->arr_map[i] == ' ' &&
			(info->arr_map[i + info->max_line_len] == '1' ||
			info->arr_map[i + info->max_line_len] == ' ')))
		ft_error("Error map: map is open\n");
	if (info->arr_map[i] == ' ')
		info->arr_map[i] = '1';
}

static void			ft_isvalid_middle_line(int i, t_map *info)
{
	if ((info->arr_map[i] == '0' || info->arr_map[i] == '2') &&
		(i % info->max_line_len == 0 || (i + 1) % info->max_line_len == 0))
		ft_error("Error map: map is open\n");
	else if (info->arr_map[i] == ' ')
	{
		if ((info->arr_map[i + 1] != '1' && info->arr_map[i + 1] != ' ') ||
			(info->arr_map[i - 1] != '1' && info->arr_map[i - 1] != ' ') ||
			(info->arr_map[i - info->max_line_len] != '1' &&
			info->arr_map[i - info->max_line_len] != ' ') ||
			(info->arr_map[i + info->max_line_len] != '1' &&
			info->arr_map[i + info->max_line_len] != ' '))
			ft_error("Error map: map is open\n");
		info->arr_map[i] = '1';
	}
	else if (ft_isalpha(info->arr_map[i]))
	{
		if (info->arr_map[i + 1] == ' ' ||
			info->arr_map[i - 1] == ' ' ||
			info->arr_map[i - info->max_line_len] == ' ' ||
			info->arr_map[i + info->max_line_len] == ' ')
			ft_error("Error map: map is open\n");
	}
}

static void			ft_isvalid_last_line(int i, t_map *info)
{
	if (info->arr_map[i] != '1' && !(info->arr_map[i] == ' ' &&
		info->arr_map[i - info->max_line_len] == '1'))
		ft_error("Error map: map is open\n");
	if (info->arr_map[i] == ' ')
		info->arr_map[i] = '1';
}

void				ft_valid_map(t_map *info)
{
	unsigned int	i;

	if (info->pos_pl == 0)
		ft_error("Error map: map hasn't position player\n");
	i = info->max_line_len;
	while (i < info->max_line_len * 2)
	{
		ft_isvalid_first_line(i, info);
		i++;
	}
	while (i < info->max_line_len * (info->count_line - 1))
	{
		if (info->arr_map[i] != '1')
		{
			ft_isvalid_middle_line(i, info);
			if (info->arr_map[i] == '2')
				info->count_sprites++;
		}
		i++;
	}
	while (i < info->max_line_len * info->count_line)
	{
		ft_isvalid_last_line(i, info);
		i++;
	}
}
