#include "cub3D.h"

void 	ft_color_wall(int side, int stepX, int stepY, t_map *map_info);
//double posX , posY ;  //  позиция x и y
//double dirX , dirY ; // вектор направления
//double planeX = 0, planeY = 0.66; // 2d raycaster версия плоскости камеры
//typedef struct s_cam {
//	double	pos_x;
//	double	pos_y;
//	double	dir_x;
//	double	dir_y;
//}			t_cam;

// (unsigned int p_x, unsigned int p_y, t_cam *cam, char way_player)
t_cam	*set_pos_player(unsigned int p_x, unsigned int p_y, char way_player)
{
	t_cam *camera;
	if (!(camera = malloc(sizeof(t_cam))))
	{
		ft_puterror_mem();
		return(NULL); // заменить все на exit???
	}

	camera->dir_x = 0;
	camera->dir_y = 0;
	camera->plane_x = 0;
	camera->plane_y = 0;
	if (way_player == 'N')
	{
		camera->dir_y = -1;
		camera->plane_x = FOV;
	}
	else if (way_player == 'S')
	{
		camera->dir_y = 1;
		camera->plane_x = -FOV;
	}
	else if (way_player == 'W')
	{
		camera->dir_x = -1;
		camera->plane_y = -FOV;
	}
	else if (way_player == 'E')
	{
		camera->dir_x = 1;
		camera->plane_y = FOV;
	}
	camera->pos_x = p_x + 0.5;
	camera->pos_y = p_y + 0.5;

	return (camera);
}




void 	ft_draw(t_map *map_info) {
	int x;
	double cameraX = 0.0;
	double rayDirX = 0.0;
	double rayDirY = 0.0;
	int mapX = 0;
	int mapY = 0;
	double sideDistX = 0.0;
	double sideDistY = 0.0;
	double deltaDistX = 0.0;
	double deltaDistY = 0.0;
	double perpWallDist = 0.0;

	int stepX = 0;
	int stepY = 0;
	int hit = 0;
	int side = 0;

	int lineHeight = 0;
	int drawStart = 0;
	int drawEnd = 0;

	double wall_x;

	x = 0;

//	map_info->mlx = mlx_init();
//	map_info->img = mlx_new_image(map_info->mlx, map_info->resolution_x, map_info->resolution_y);
//	map_info->addr = mlx_get_data_addr(map_info->img, &map_info->bits_per_pixel, &map_info->line_length, &map_info->endian);

	while (x < map_info->resolution_x) {
		cameraX = 2 * x / (double) map_info->resolution_x - 1;
		rayDirX = map_info->cam->dir_x + (cameraX * map_info->cam->plane_x);
		rayDirY = map_info->cam->dir_y + (cameraX * map_info->cam->plane_y);

		mapX = (int) floor(map_info->cam->pos_x);
		mapY = (int) floor(map_info->cam->pos_y);

		deltaDistX = fabs(1 / rayDirX);
		deltaDistY = fabs(1 / rayDirY);
		hit = 0;
		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = (map_info->cam->pos_x - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - map_info->cam->pos_x) * deltaDistX;
		}
		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = (map_info->cam->pos_y - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - map_info->cam->pos_y) * deltaDistY;
		}

		while (hit == 0) {
			if (sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			} else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (map_info->arr_map[mapX + (mapY * map_info->max_line_len)] == '1')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - map_info->cam->pos_x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - map_info->cam->pos_y + (1 - stepY) / 2) / rayDirY;

		ft_color_wall(side, stepX, stepY, map_info);

		lineHeight = (int) (map_info->resolution_y / perpWallDist);
		drawStart = -lineHeight / 2 + map_info->resolution_y / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + map_info->resolution_y / 2;
		if (drawEnd >= map_info->resolution_y)
			drawEnd = map_info->resolution_y - 1;

		// for textures needed
		if (side == 0)
			wall_x = map_info->cam->pos_y + perpWallDist * rayDirY;
		else
			wall_x = map_info->cam->pos_x + perpWallDist * rayDirX;
		wall_x -= floor(wall_x);
		//
		if (side == 1 && stepY < 0)
			draw_txtr(map_info,map_info->wall_n, x, drawStart, drawEnd, wall_x, lineHeight);
		else if (side == 1 && stepY > 0)
			draw_txtr(map_info,map_info->wall_s, x, drawStart, drawEnd, wall_x, lineHeight);
		else if (side == 0 && stepX < 0)
			draw_txtr(map_info,map_info->wall_e, x, drawStart, drawEnd, wall_x, lineHeight);
		else if (side == 0 && stepX > 0)
			draw_txtr(map_info,map_info->wall_w, x, drawStart, drawEnd, wall_x, lineHeight);
//		написать функцию отрисовки потолка и пола
		ft_draw_floor_ceiling(map_info, x, drawStart, drawEnd);
//			draw_ver_line(map_info, x, drawStart, drawEnd);
		x++;
	}
}

void 	ft_render(t_map *map_info)
{
	ft_draw(map_info);
	mlx_put_image_to_window(map_info->mlx, map_info->win, map_info->img, 0, 0);
	mlx_destroy_image(map_info->mlx, map_info->img);
	mlx_loop_hook(map_info->mlx, ft_render_next, map_info);
	mlx_hook(map_info->win, KEYPRESS, KeyPressMask, ft_key_press, map_info);
	mlx_hook(map_info->win, KEYRELEASE, KeyReleaseMask, ft_key_release, map_info);
	mlx_hook(map_info->win, DestroyNotify, StructureNotifyMask, ft_close, map_info);
//	mlx_hook(map_info->win, KEYPRESS, KeyPressMask, ft_close, map_info);
	mlx_loop(map_info->mlx);
}

void 	ft_color_wall(int side, int stepX, int stepY, t_map *map_info)
{
//	map_info->color_wall = 0x00FF00;
	if (side == 1)
	{
		if (stepY < 0)
			map_info->color_wall = 0x3088AA; //north
		else //if (stepY < 0)
			map_info->color_wall = 0xAA70AA; // south
	}
	else //if (side == 0)
	{
		if (stepX < 0)
			map_info->color_wall = 0x550000; //	east
		else //if (stepX > 0)
			map_info->color_wall = 0x110455; //	west
	}
}

