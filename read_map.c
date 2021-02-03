//
// read map and check error
// malloc: line, map_info;
//
#include <minilibx_mms_20200219/mlx.h>
#include "cub3D.h"

// -1 - error, 1 - success
int 	ft_append_buf(char **line, char *buf)
{
	char 	*tmp;
	int 	i;

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

// аналог гнл, возвращает -1 если ошибка, 1 и 0 в случае успешного считывания файла
int 	ft_read_line(int fd, char **line)
{
	static char	buf[2];
	int 		n;

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

// 	добавить функцию в libft
int		ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r' ||
		c == '\f' || c == '\v')
		return (1);
	return (0);
}

// как обрабатывать тут ошибки
void	ft_check_resolution(char *line, t_map *map_info)
{
	int 			i;
	int		x;
	int		y;

	i = 0;
	if ((map_info->resolution_x = ft_atoi(line)) <= 0)
		return;
	while (ft_isspace(line[i]))
		i++;
	while (ft_isdigit(line[i]))
		i++;
	if ((map_info->resolution_y = ft_atoi(&line[i])) <= 0)
		return;
	// проверять не привышает ли разрешение экрана
	mlx_get_screen_size(map_info->mlx, &x, &y);
	printf("res_x = %d  res_y = %d \n", map_info->resolution_x, map_info->resolution_y);
	printf("x = %d  y = %d \n", x, y);
}

// получаем цвет
int		ft_create_trgb_color(int t, int r, int g, int b)
{
	return(t << 24 | r << 16 | g << 8 | b);
}

// какие могут быть ошибки 	ещё??
// если цвет меньше 0 или больше 255.
void 	ft_get_color(char *line, t_map *map_info)
{
	int 	i;
	int 	red;
	int 	green;
	int 	blue;

	i = 0;
	while (!ft_isdigit(line[i]) && line[i] != '\0')
		i++;
	red = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	i++;
	green = ft_atoi(&line[i]);
	while (ft_isdigit(line[i]))
		i++;
	i++;
	blue = ft_atoi(&line[i]);
	if (red < 0 || red > 255 || blue < 0 || blue > 255 || green < 0 || green > 255)
	{
		write(2, "Error map: RGB color not in range [0,255]\n", 42);
		exit(1);
	}
	if (line[0] == 'F')
		map_info->floor_color = ft_create_trgb_color(0, red, green, blue);
	if (line[0] == 'C')
		map_info->ceilling_color = ft_create_trgb_color(0, red, green, blue);
	return;
}

// как обрабатывать тут ошибки
int		ft_check_texture(char *line, t_map *map_info)
{
	int 	i;
	int		len;

	i = 0;
	// проверять если данная текстура (N,S,W,E) уже заполнена, то выходить с ошибкой
	while (line[i] != ' ')
		i++;
	while (ft_isprint(line[i]))
	{
		len++;  //?? нужна ли длина строки
		i++;// отсечь если есть пробелы в конце
		// проверить что можно пройти и получить xpm
//		перевести xpm в img и хранить указатель на текстуру
// если путь не верный, то возвращать ошибку

	}
}

// нужно ли что-то возвращать?? если нет, то сделать void
// определить возврат 1 и 0?
int 	ft_parse_line(char *line, t_map *map_info)
{
	int		i;
	static int flag_split;
	i = 0;
	if (!line)
		return (0); // вернуть ошибку??
//		оптимизировать проверку пустых строк
	if (line[0] == '\0')
	{
		if (map_info->start_row != NULL)
			flag_split = 1;
		free(line);
		return (1);
	}
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == 'R')
		ft_check_resolution(&line[i + 1], map_info);
	else if(line[i] == 'N' || line[i] == 'S' || line[i] == 'W' || line[i] == 'E')
		ft_check_texture(&line[i], map_info);
	else if (line[i] == 'F' || line[i] == 'C')
		ft_get_color(&line[i], map_info);
	else if (line[i] == '\0')
	{
		if (map_info->start_row != NULL)
			flag_split = 1;
		free(line);
		return (1);
	}
	else
	{
		if (flag_split == 1)
		{
			write(2, "Error map: map is split\n", 24);
			exit(1);
		}
		ft_copy_map(line, map_info); // анализировать ошибки?
	}
	if (line != NULL)
		free(line);
	return (1);
}

void	ft_init_info(t_map	*map_info)
{
	int i;

	i = 0;
	while (i < 8)
		map_info->key[i++][0] = 0;
	// key[8]: 0 = A; 1 = S; 2 = D; 3 = W; 4 = left; 5 = right;
	map_info->key[0][1] = KEY_A;
	map_info->key[1][1] = KEY_S;
	map_info->key[2][1] = KEY_D;
	map_info->key[3][1] = KEY_W;
	map_info->key[4][1] = KEY_LEFT;
	map_info->key[5][1] = KEY_RIGTH;

	map_info->resolution_x = 0;
	map_info->resolution_y = 0;
	map_info->north_txtr = NULL;
	map_info->south_txtr = NULL;
	map_info->west_txtr = NULL;
	map_info->east_txtr = NULL;
	map_info->sprite_txtr = NULL;
	map_info->floor_color = 0;
	map_info->ceilling_color = 0;
	map_info->count_line_in_map = 0;
	map_info->max_line_len = 0;
	map_info->start_row = NULL;
	map_info->last_row = NULL;
	map_info->position_player = 0;
	map_info->arr_map = NULL;
}


void	ft_read_map(char *file, t_map *map_info)
{
	int		fd;
	int		n;
	char 	*line;

	if ((fd = open(file, 0)) == -1)
		return (ft_puterror()); // ошибка чтения карты исп perror, strerror ?
	while ((n = ft_read_line(fd, &line)) > 0)
		ft_parse_line(line, map_info);
	if (n == 0)
	{
//		поставить проверку того что последняя строка состоит из 1
//		или неписать функцию отдельно, так как если раскомментировать
//		то в подсчеты будет добавляться еще одна строка
//		if (ft_contents_of_line(line, map_info, "1 ") != 1)
//			return; //возвращать ошибку, отчищать память ошибка последней строки карты
//			или выходить по 	exit(1)
		ft_parse_line(line, map_info);
		ft_create_arr_map(map_info); // поставить проверки?
		map_info->wall_n = ft_paint_texture(WAY_T_N, map_info->mlx); //(char *file, void *ptr_mlx)
		map_info->wall_s = ft_paint_texture(WAY_T_S, map_info->mlx);
		map_info->wall_e = ft_paint_texture(WAY_T_E, map_info->mlx);
		map_info->wall_w = ft_paint_texture(WAY_T_W, map_info->mlx);
		ft_render(map_info);

	}
	if (n == -1)
	{
		if (line != NULL)
			free(line);
		return (ft_puterror()); // ошибка при чтении файла
	}
	if (close(fd) == -1) // ошибка закрытия файла
		return (ft_puterror());
}


