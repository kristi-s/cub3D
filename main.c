/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <droslyn@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 00:41:35 by droslyn           #+#    #+#             */
/*   Updated: 2021/03/19 02:01:24 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		main(int argc, char **argv)
{
	t_map	*info;

	if (argc == 2 || argc == 3)
	{
		ft_check_extension(argv[1], ".cub");
		if (!(info = malloc(sizeof(t_map))))
			ft_error("Error memory allocation\n");
		ft_init_info(info, 0);
		info->file = argv[1];
		if (argc == 3 && (ft_strncmp(argv[2], "--save", 6) == 0))
			info->flag_save = 1;
		else
			info->flag_save = 0;
		ft_read_map(info);
		return (0);
	}
	else
		write(2, "Error: wrong number of arguments\n", 26);
	return (0);
}
