//
// на вход первый аргумент карта c расширением .cub
// карта должна состоять только из 4 возможных символов:
// 0 для пустого пространства, 1 для стены, 2 для предмета
// и N,S,E или W для начальной позиции игрока

// 		валидность карты:
// 1) Карта должна быть закрыта / окружена стенами,
// если нет, то программа должна вернуть ошибку.
// 2) За исключением содержимого карты,
// каждый тип элемента может быть разделен одной или неск пустыми строками.
// 3) За исключением содержимого карты,
// которое всегда должно быть последним,
// каждый тип элемента может быть установлен в любом порядке в файле.
// 4) За исключением карты, каждый тип информации от элемента
// может быть отделен одним или несколькими пробелами.
// 5) Карта должна быть проанализирована так, как она выглядит в файле.
// Пробелы являются действительной частью карты.
// Вы должны быть в состоянии разобрать любой вид карты, если он соблюдает правила карт.
// 6) Каждый элемент (кроме карты) первой информацией является идентификатор типа
// (состоящий из одного или двух символов),
// за которым следует Вся конкретная информация для каждого объекта в строгом порядке.
// 7) Если в файле обнаружена какая-либо неправильная конфигурация,
// программа должна правильно выйти и вернуть "Error\n",
// а затем явное сообщение об ошибке по вашему выбору.
//
// если указан
// второй арг --save, то нужно сохнить скриншот первого экрана
//
// -> <- на клавиатуре должны смотреть влево и вправо в лабиринте.
// Клавиши W, A,S и D должны перемещать точку зрения по лабиринту.
// нажатие ESC - закрыть окно и полностью выйти из программы.
// нажатие на красный крестик в окне - аналогично ESC.
// Если заявленный размер экрана на карте больше разрешения дисплея,
// то размер окна будет установлен в зависимости от текущего разрешения дисплея.
//

#include "cub3D.h"

typedef struct  s_vars {
	void    *mlx;
	void    *win;
}               t_vars;

int		main(int argc, char **argv)
{
	int i;
	t_map	*map_info;
//	t_data data;
//	t_vars vars;

	i = 1;
	if (argc == 2 || argc == 3)
	{
		if (!(map_info = malloc(sizeof(t_map))))
			return(0); // возвращать ошибку? ft_puterror_mem()

			//parse
			//init
		ft_init_info(map_info);
//		map_info->resolution_y = 1440;
//		map_info->resolution_x = 2560;
//перенести все в др место
//		map_info->mlx = mlx_init();
//		map_info->win = mlx_new_window(map_info->mlx, map_info->resolution_x, map_info->resolution_y, argv[1]);
//		map_info->img = mlx_new_image(map_info->mlx, map_info->resolution_x, map_info->resolution_y);
//		map_info->addr = mlx_get_data_addr(map_info->img, &map_info->bits_per_pixel, &map_info->line_length, &map_info->endian);

//		my_mlx_pixel_put(map_info, 10, 10, 0xFF0000);
//		mlx_put_image_to_window(map_info->mlx, map_info->win, map_info->img, 0, 0);
//
//		mlx_loop(map_info->mlx);

		map_info->file = argv[1];
		ft_read_map(map_info);


//		void *mlx;
//		void *win;
//		t_data data;
//		t_vars vars;
//
//		vars.mlx = mlx_init();
//		data.img = mlx_new_image(vars.mlx, map_info->resolution_x, map_info->resolution_y);
//		data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

		return (0);
	}
	else
		write(1, "Error: too many arguments\n",26);
	return (0);
}

/*
typedef struct	s_data {
	void *img;
	char *addr; //pointer to pixels array
	int bits_per_pixel; //32 bit
	int line_length; //width
	int endian;
}				t_data;

typedef struct  s_vars {
	void    *mlx;
	void    *win;
}               t_vars;

void 	my_mlx_pixel_put(t_data *img, int x, int y, int color) {
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
//
void 	draw_ver_line(t_data *img, int x, int y0, int y1) {
	int color = 0x00FF00;

	for (int i = y0; i <= y1; i++) {
		my_mlx_pixel_put(img, x, i, color);
	}
}

//int             ft_close(int keycode, t_vars *vars)
//{
//	mlx_destroy_window(vars->mlx, vars->win);
//	exit(1);
//}


int 	main(int argc, char **argv) {
	(void)argc;
	(void)argv;

//	void *mlx;
	t_data data;
	t_vars vars;

	vars.mlx = mlx_init();
	data.img = mlx_new_image(vars.mlx, 1000, 800);
//	void *win;

	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	int x = 50;
	int y0 = 100;
	int y1 = 200;
	int delta = 2;

	while (x < 800) {
		while (y0 + delta < y1) {
			draw_ver_line(&data, x, y0, y0 + delta);
			delta += 2;
			x += 5;
		}
		y1+=100;
		x+=20;


	}


	vars.win = mlx_new_window(vars.mlx, 1000, 600, "cub3D"); //check null
	mlx_put_image_to_window(vars.mlx, vars.win, data.img, 0, 0);

//	mlx_hook(vars.win, 2, 1L<<0, ft_close, &vars);
	mlx_loop(vars.mlx);


	return 0;
}*/


//проверка валидности аргументов
//считывание карты
//проверка валидности
//разбор данных
//инициализация mlx
//raycasting
//движение игрока
//возможность сделать скрин
