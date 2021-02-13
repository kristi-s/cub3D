//
// malloc: line, map_info // приходят на вход
//
#include "cub3D.h"

// в copy_map может попасть строка,
// если в ней есть что-то кроме пробелов
int 	ft_contents_of_line(char *line, t_map *map_info, char *content)
{
	int		i;

	i = 0;
	// проверка если строка пустая пропускать её
	while(ft_isspace(line[i]))
		i++;
//	if (line[i] == '\0')
//	{
//		if (map_info->start_row != NULL)
//		{
//			write(2, "Error map: map is split\n", 24);
//			exit(1);
//		}
//		return (1);
//	}
	i = 0;
	//выдавать ошибку если пустая строка в середине карты не должно быть пустых стр)
	// сохранять максимальную длину строки
	map_info->count_line_in_map++; // cчитаем к-во строк
	if (ft_strlen(line) > map_info->max_line_len)
		map_info->max_line_len = ft_strlen(line);
	while(line[i] != '\0' && ft_strchr(content, line[i]))
	{
		if (ft_isalpha(line[i]))
		{
			if (map_info->position_player == 0)
			{
				map_info->position_player = line[i];
//				printf("strart: %d %d  |", i, map_info->count_line_in_map - 1);
//		добавить (count_line - 1), если не будем добавлять в карту строку с единицами вначале
				map_info->cam = set_pos_player(i, map_info->count_line_in_map, map_info->position_player); ////ставить проверки
				//(unsigned int p_x, unsigned int p_y, char way_player)
			}
			// определять положение игрока
			else
			{
// ошибка "заданно несколько позиций игрока"
				write(2, "Error map: more than one position player\n", 41);
				exit(1);
			}

		}
		i++;
	}
	if (line[i] == '\0')
		return (1);
	return (0);
}
// ft_contents_of_line возвращает 1 - если состоит строка состоит только из строки content
// позиция играка НЕ инициализирована повторно.
// -1 - ошибка: повторная инициализация позиции игрока
// 0 - строка содержит не валидные символы.

int 	ft_copy_map(char *line, t_map *map_info)
{
	t_list	*newlist;
	char 	*copy_line;

	if (!(copy_line = ft_strdup(line)))
		return (-1); // возвращать ошибку???
	if (!(newlist = ft_lstnew(copy_line)))
		return (-1);// возвращать ошибку???
	if (!map_info->start_row)
	{
		if (ft_contents_of_line(line, map_info, "1 ") == 1)
		{
			map_info->start_row = newlist;
			map_info->last_row = newlist;
		}
		else
		{
// ошибка "в первой строке есть символы кроме "1 " "
			write(2, "Error map: not valid first line of map\n", 39);
			exit(1);
		}
	}
	else
	{
		if (ft_contents_of_line(line, map_info, "012NSWE ") == 1)
		{
			ft_lstadd_back(&map_info->last_row, newlist);
			map_info->last_row = newlist;
		}
		else
		{
// ошибка "в строке есть символы кроме "012NSWE " "
			write(2, "Error map: not valid simbol in line of map\n", 43);
			exit(1);
		}
	}
	return (1);
}


void	ft_create_arr_map(t_map *map_info)
{
	unsigned int	size_arr;
	t_list			*ptr_line;
	int 			i;
	int 			count;

//	printf("len = %d, count line = %d \n", map_info->max_line_len, map_info->count_line_in_map);
	map_info->count_line_in_map++;
	size_arr = map_info->max_line_len * map_info->count_line_in_map;
	if (!(map_info->arr_map = malloc(sizeof(char) * size_arr)))
		return(ft_puterror_mem());

	count = 0;
	while (count < map_info->max_line_len)
		map_info->arr_map[count++] = '1';
	ptr_line = map_info->start_row;
	i = 0;
	while(ptr_line != NULL)
	{
		while(((char *)ptr_line->content)[i] != '\0')
		{
			map_info->arr_map[count] = ((char *)ptr_line->content)[i];
			i++;
			count++;
		}
		while (i < map_info->max_line_len)
		{
			map_info->arr_map[count] = ' ';
			i++;
			count++;
		}
		ptr_line = ptr_line->next;
		i = 0;
	}
	ft_valid_map(map_info);
//	после того как карта завалидирована и посчитано количество спрайтов
//	для отладки
	printf("map ok \n");
//	i = 0;
//	while (i < size_arr)
//	{
//		printf("%c|", map_info->arr_map[i]);
//		if ((i + 1) % map_info->max_line_len == 0)
//			printf("\n");
//		i++;
//	}
//	printf("\n");
	//////////
}
