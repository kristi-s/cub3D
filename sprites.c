//
// Created by Кристина Смирнова on 12.02.2021.
//
#include "cub3D.h"

//нужно ли количество спрайтов сохранять в структуру
// или сделать переменную и передавать её на вход??


//запуск после валидации карты
void	ft_count_sprite(t_map *map_info)
{
	int 	i;
	int		ind;

	i = 0;
	ind = 0;
	if (map_info->count_sprites == 0)
		return;
	if (!(map_info->arr_sprites = malloc(map_info->count_sprites * sizeof(int))))
		ft_error("Error memory allocation\n");
	while (i < (map_info->max_line_len * map_info->count_line_in_map))
	{
		if (map_info->arr_map[i] == '2')
		{
			map_info->arr_sprites[ind] = i;
			ind++;
		}
		i++;
	}

//	выделили память для Z_Buffer
	if (!(map_info->z_buff = malloc(map_info->resolution_x * sizeof(double))))
		ft_error("Error memory allocation\n");

//	удалить отладочную печать!!!
	i = 0;
	while (i < map_info->count_sprites)
	{
		printf("%d | ", map_info->arr_sprites[i]);
		i++;
	}
}


//сортирует от дальнего до ближнего
void	ft_sort(double *array_spr, int *n_spr, t_map *map_info)
{
	int i;
	int j = 0;
	double tmp;
	int temp_i;

	while(j < map_info->count_sprites - 1)
	{
		i = 0;
		while (i < map_info->count_sprites - j - 1)
		{
			if (array_spr[i] < array_spr[i + 1])
			{
				tmp = array_spr[i];
				array_spr[i] = array_spr[i + 1];
				array_spr[i + 1] = tmp;
				temp_i = n_spr[i];
				n_spr[i] = n_spr[i + 1];
				n_spr[i + 1] = temp_i;
			}
			i++;
		}
		j++;
	}

	// для отладки
//	i = 0;
//	while (i < map_info->count_sprites) {
//		printf("%f | ", array_spr[i]);
//		i++;
//	}

}