#include "cub3D.h"

void 	ft_turn(t_cam *cam, int way);
void 	ft_move(t_cam *cam, char *arr_map, unsigned int size, int way);

int 	ft_close(int keycode, t_map *info)
{
//	printf("ft_close: keycode = %d\n", keycode);
	if (keycode != KEY_ESC)
		return (0);
	mlx_destroy_window(info->mlx, info->win);
	exit(0);
}

// key[][]: 0 = A; 1 = S; 2 = D; 3 = W; 4 = left; 5 = right;
void 	ft_key_change(int keycode, char status, int key[6][2])
{
	int i;

	i = 0;
	if (keycode == KEY_ESC) {
//		нужно ли делать эту функцию? или достаточно exit???
//		mlx_destroy_window(map_info->mlx, map_info->win);
		exit(0);
	}
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

int 	ft_key_press(int keycode, t_map *info)
{
	ft_key_change(keycode, 1, info->key);
	return (0);
}

int 	ft_key_release(int keycode, t_map *info)
{
	ft_key_change(keycode, 0, info->key);
	return (0);
}

void 	ft_choose_action(int i, t_map *info)
{
	while(i < 6)
	{
		if (info->key[i][0] == 1)
		{
			if (i <= 3)
				ft_move(info->cam, info->arr_map, info->max_line_len, info->key[i][1]);
			else
				ft_turn(info->cam, info->key[i][1]);

		}
		i++;
	}
}


int     ft_render_next(t_map *info)
{
	int i;

	i = 0;
	while (i < 6 && info->key[i][0] == 0)
		i++;
	if (i == 6)
		return (0);
	mlx_do_sync(info->mlx);
	ft_choose_action(i, info);

	// сделать ft_render ???
	info->img = mlx_new_image(info->mlx, info->w, info->h);
	if (!info->img)
		ft_error("Error: create new image fail\n");
	info->addr = mlx_get_data_addr(info->img, &info->bits_per_pixel, \
		&info->line_length, &info->endian);
	ft_draw(info);
	mlx_put_image_to_window(info->mlx, info->win, info->img, 0, 0);
	mlx_destroy_image(info->mlx, info->img);
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

// добавить проверку о выхода за границы массива
// 	если карта закрыта, то не будет выходить за границы ????
	if (arr_map[(int)(new_x) + ((int)(new_y) * size)] != '1')
	{
		cam->pos_x = new_x;
		cam->pos_y = new_y;
	}
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


