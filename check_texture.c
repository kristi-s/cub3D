/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <droslyn@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 01:42:56 by droslyn           #+#    #+#             */
/*   Updated: 2021/03/19 01:51:37 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		ft_error("Error map: error texture or map is open\n");
	return (0);
}

void			ft_check_texture(char *line, t_map *info, int i)
{
	int			len;
	char		*ptr;
	char		**adr;

	adr = ft_switch_txtr(line, info);
	i = 1;
	if (line[i] != ' ')
		i++;
	while (ft_isspace(line[i]))
		i++;
	len = 0;
	while (line[i] >= 33 && line[i] <= 126)
	{
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
