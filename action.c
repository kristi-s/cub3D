#include "cub3D.h"

void 	ft_turn(t_cam *cam, int way);
void 	ft_move(t_cam *cam, char *arr_map, unsigned int size, int way);

int 	ft_close(int keycode, t_map *map_info)
{
//	printf("ft_close: keycode = %d\n", keycode);
	if (keycode != KEY_ESC)
		return (0);
	mlx_destroy_window(map_info->mlx, map_info->win);
	exit(0);
}

// key[][]: 0 = A; 1 = S; 2 = D; 3 = W; 4 = left; 5 = right;
void 	ft_key_change(int keycode, char status, int key[6][2])
{
	int i;

	i = 0;
	while (i < 6)
	{
		if (keycode == key[i][1])
		{
			key[i][0] = status;
			return;
		}
		i++;

	}

//	if (keycode == KEY_A)
//		key[0][0] = status;
//	else if (keycode == KEY_S)
//		key[1][0] = status;
//	else if (keycode == KEY_D)
//		key[2][0] = status;
//	else if (keycode == KEY_W)
//		key[3][0] = status;
//	else if (keycode == KEY_LEFT)
//		key[4][0] = status;
//	else if (keycode == KEY_RIGTH)
//		key[5][0] = status;
}

int 	ft_key_press(int keycode, t_map *map_info)
{
	ft_key_change(keycode, 1, map_info->key);
	return (0);
}

int 	ft_key_release(int keycode, t_map *map_info)
{
	ft_key_change(keycode, 0, map_info->key);
	return (0);
}

void 	ft_choose_action(int i, t_map *map_info)
{
	while(i < 6)
	{
		if (map_info->key[i][0] == 1)
		{
			if (i <= 3)
				ft_move(map_info->cam, map_info->arr_map, map_info->max_line_len, map_info->key[i][1]);
			else
				ft_turn(map_info->cam, map_info->key[i][1]);

		}
		i++;
	}
}

//mlx_do_sync(sv->mlx);
//	check_buttons_state(sv);
//	sv->img.img = mlx_new_image(sv->mlx, sv->map.res_w, sv->map.res_h);

//	ft_alloc_check(sv->img.img);
//	sv->img.addr = mlx_get_data_addr(sv->img.img, &sv->img.bits_per_pixel, \
//									&sv->img.line_length, &sv->img.endian);
//	set_sprites_coordinates(sv);
//	cast_frame(sv);
//	mlx_put_image_to_window(sv->mlx, sv->win, sv->img.img, 0, 0);
//	mlx_destroy_image(sv->mlx, sv->img.img);
//	if (PRINT_FRAME_NUMBER)
//		print_frame_number();
//	return (0);

int     ft_render_next(t_map *map_info)
{
	int i;

	i = 0;
	while (i < 6 && map_info->key[i][0] == 0)
		i++;
	if (i == 6)
		return (0);
	mlx_do_sync(map_info->mlx);
	ft_choose_action(i, map_info);

	// сделать ft_render ???
	map_info->img = mlx_new_image(map_info->mlx, map_info->resolution_x, map_info->resolution_y);
	if (!map_info->img)
		exit(1); // добавить сообщение от ошибке (сделать ft_exit)
	map_info->addr = mlx_get_data_addr(map_info->img, &map_info->bits_per_pixel, \
		&map_info->line_length, &map_info->endian);
	ft_draw(map_info);
	mlx_put_image_to_window(map_info->mlx, map_info->win, map_info->img, 0, 0);
	mlx_destroy_image(map_info->mlx, map_info->img);
	return (0);
}

// call ft_move(map_info->cam, map_info->arr_map, map_info->max_line_len, keycode)
// передавать целиком map_info
void 	ft_move(t_cam *cam, char *arr_map, unsigned int size, int way)
{
	double delta_x; // если что можно перенести во входные параметры
	double delta_y;
	double new_x; //можно оставить без использования переменной
	double new_y;
	int dir;

	dir = 1; //если W or D то будет 1
	if (way == KEY_S || way == KEY_A)
		dir = -1;
	if (way == KEY_S || way == KEY_W)
	{
		delta_x = cam->dir_x * MOVE_SPEED;
		delta_y = cam->dir_y * MOVE_SPEED;
	}
	else // 	в случае если A or D
	{
		delta_x = cam->plane_x * MOVE_SPEED;
		delta_y = cam->plane_y * MOVE_SPEED;
	}
	new_x = cam->pos_x + (dir * delta_x);
	new_y = cam->pos_y + (dir * delta_y);
//	printf("\n| pos x = %f %f ", cam->pos_x, cam->pos_y);
// добавить проверку о выхода за границы массива
//	if ((int)(new_x + 0.3) + ((int)(new_y + 0.3) * size) < 0 ||
//			(int)(new_x + 0.3) + ((int)(new_y + 0.3) * size) > size * map_info->count  )
	if (arr_map[(int)(new_x) + ((int)(new_y) * size)] != '1')
	{
//	if (arr_map[(int)(new_x + 0.4) + ((int)(cam->pos_y + 0.4) * size)] != '1')
		cam->pos_x = new_x;
//	if (arr_map[(int)(cam->pos_x + 0.4) + ((int)(new_y + 0.4) * size)] != '1')
		cam->pos_y = new_y;
	}
//	printf("| arr = %d ", size);
//	printf("| pos new = %f %f ", new_x, new_y);
}

// call ft_turn(map_info->cam, keycode)
void 	ft_turn(t_cam *cam, int way)
{
	double  cur_dir_x;
	double 	cur_plane_x;
	int 	dir;
	double 	delta_sin;
	double 	delta_cos;

	dir = 1; //if KEY_RIGHT, then 1
	if (way == KEY_LEFT)
		dir = -1;
	cur_dir_x = cam->dir_x;
	cur_plane_x = cam->plane_x;
	delta_sin = sin(dir * ROTATION);
	delta_cos = cos(dir * ROTATION);
	cam->dir_x = cam->dir_x * delta_cos - cam->dir_y * delta_sin;
	cam->dir_y = cur_dir_x * delta_sin + cam->dir_y * delta_cos;
	cam->plane_x = cam->plane_x * delta_cos - cam->plane_y * delta_sin;
	cam->plane_y = cur_plane_x * delta_sin + cam->plane_y * delta_cos;
}


