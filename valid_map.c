#include "cub3D.h"

// unsigned int	count_line_in_map;
//	unsigned int 	max_line_len;
// char 			*arr_map;


// проверить получается ли открыть файлы текстур !!!!!


void		ft_valid_map(t_map *map_info)
{
	int i;

	if (map_info->position_player == 0)
	{
		write(2, "Error map: map hasn't position player\n", 38);
		exit(1);
	}

	i = map_info->max_line_len;
//	i = map_info->max_line_len * 2; // по строке
	while (i < map_info->max_line_len * 2)
	{
//		если =0 или над пробелом 0
		if (map_info->arr_map[i] != '1' &&
			!(map_info->arr_map[i] == ' ' &&
					(map_info->arr_map[i + map_info->max_line_len] == '1' ||
					map_info->arr_map[i + map_info->max_line_len] == ' ')))
			ft_error("Error map: map is open\n");
//		{
//			write(2, "Error map: map is open\n", 23);
//			exit(1);
//		}
		if (map_info->arr_map[i] == ' ')
			map_info->arr_map[i] = '1';
		i++;
	}
//	проверять со второй строки до предпоследней
	while (i < map_info->max_line_len * (map_info->count_line_in_map - 1)) {
//		если == 1 то просто наращиваем счетчик
		if (map_info->arr_map[i] != '1')
		{
//			выходим с ошибкой, если первый или посл симв в стр =0
			if (map_info->arr_map[i] == '0' &&
					(i % map_info->max_line_len == 0 || (i + 1) % map_info->max_line_len == 0))
			{
				write(2, "Error map: map is open\n", 23);
//удалить printf!!!
				printf("i = %d\n", i);
				exit(1);
			}
//			если пробел, то смотрим с трeх сторон
			else if (map_info->arr_map[i] == ' ')
			{
				if ((map_info->arr_map[i + 1] != '1' && map_info->arr_map[i + 1] != ' ') ||
					(map_info->arr_map[i - 1] != '1' && map_info->arr_map[i - 1] != ' ') ||
					(map_info->arr_map[i - map_info->max_line_len] != '1' && map_info->arr_map[i - map_info->max_line_len] != ' ')||
					(map_info->arr_map[i + map_info->max_line_len] != '1' && map_info->arr_map[i + map_info->max_line_len] != ' '))
				{
					write(2, "Error map: map is open\n", 23);
//удалить printf!!!
					printf("i = %d\n", i);
					exit(1);
				}
				map_info->arr_map[i] = '1';
			}
			else if (ft_isalpha(map_info->arr_map[i]))
			{
				if (map_info->arr_map[i + 1] == ' ' ||
					map_info->arr_map[i - 1] == ' ' ||
					map_info->arr_map[i - map_info->max_line_len] == ' ' ||
					map_info->arr_map[i + map_info->max_line_len] == ' ')
				{
					write(2, "Error map: map is open\n", 23);
//удалить printf!!!
					printf("i = %d\n", i);
					exit(1);
				}
			}
			else if (map_info->arr_map[i] == '2')
				map_info->count_sprites++;
		}
		i++;
	}
	while (i < map_info->max_line_len * map_info->count_line_in_map)
	{
//		если =0 или над пробелом 0
		if (map_info->arr_map[i] != '1' &&
			!(map_info->arr_map[i] == ' ' &&
			map_info->arr_map[i - map_info->max_line_len] == '1'))
		{
			write(2, "Error map: map is open\n", 23);
//удалить printf!!!
			printf("i = %d\n", i);
			exit(1);
		}
		if (map_info->arr_map[i] == ' ')
			map_info->arr_map[i] = '1';
		i++;
	}

}