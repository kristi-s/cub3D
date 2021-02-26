#include "cub3D.h"

//void 	ft_draw_sprites(t_map *info);

static void 	ft_init_cam(unsigned int p_x, unsigned int p_y, t_cam *camera)
{
	camera->dir_x = 0;
	camera->dir_y = 0;
	camera->plane_x = 0;
	camera->plane_y = 0;
	camera->pos_x = p_x + 0.5;
	camera->pos_y = p_y + 0.5;
}

t_cam	*set_pos_player(unsigned int p_x, unsigned int p_y, char way_player)
{
	t_cam *camera;
	if (!(camera = malloc(sizeof(t_cam))))
		ft_error("Error memory allocation\n");
	ft_init_cam(p_x, p_y, camera);
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
	return (camera);
}

void	ft_init_cam_other(t_cam *cam);
//{
//	cam->camera_x = 0.0;
//	cam->ray_dir_x = 0.0;
//	cam->ray_dir_y = 0.0;
//	cam->map_x = 0;
//	cam->map_y = 0;
//	cam->delta_dist_x = 0.0;
//	cam->delta_dist_y = 0.0;
//	cam->side_dist_x = 0.0;
//	cam->side_dist_y = 0.0;
//	cam->perp_wall_dist = 0.0;
//	cam->step_x = 0;
//	cam->step_y = 0;
//	cam->side = 0;
//	cam->line_height = 0;
//	cam->draw_start = 0;
//	cam->draw_end = 0;
//	cam->wall_x = 0.0;
//
//}

void 	ft_one(int w, int x, t_cam *cam);
//{ // вычисляем положение луча и направление
//	cam->camera_x = 2 * x / (double)w - 1;
//	cam->ray_dir_x = cam->dir_x + (cam->camera_x * cam->plane_x);
//	cam->ray_dir_y = cam->dir_y + (cam->camera_x * cam->plane_y);
//	cam->map_x = (int) floor(cam->pos_x);
//	cam->map_y = (int) floor(cam->pos_y);
//	cam->delta_dist_x = fabs(1 / cam->ray_dir_x);
//	cam->delta_dist_y = fabs(1 / cam->ray_dir_y);
//	if (cam->ray_dir_x < 0) {
//		cam->step_x = -1;
//		cam->side_dist_x = (cam->pos_x - cam->map_x) * cam->delta_dist_x;
//	} else {
//		cam->step_x = 1;
//		cam->side_dist_x = (cam->map_x + 1.0 - cam->pos_x) * cam->delta_dist_x;
//	}
//	if (cam->ray_dir_y < 0) {
//		cam->step_y = -1;
//		cam->side_dist_y = (cam->pos_y - cam->map_y) * cam->delta_dist_y;
//	} else {
//		cam->step_y = 1;
//		cam->side_dist_y = (cam->map_y + 1.0 - cam->pos_y) * cam->delta_dist_y;
//	}
//}

void 	ft_two(int x, t_cam *cam, t_map *info);
void 	ft_three(int h, t_cam *cam);
void 	ft_four(int x, t_cam *cam, t_map *info);
void 	ft_find_dist_spr(t_map *info);
void 	ft_calc_spr(t_map *info, t_sprt *spr, t_cam *cam, int ind);
void 	ft_draw_spr(t_map *info, t_sprt *spr, int txt_w, int txt_h);
void 	ft_draw(t_map *info) {
	int x;
/*/	double cameraX = 0.0;
//	double rayDirX = 0.0;
//	double rayDirY = 0.0;
//	int mapX = 0;
//	int mapY = 0;
//	double sideDistX = 0.0;
//	double sideDistY = 0.0;
//	double deltaDistX = 0.0;
//	double deltaDistY = 0.0;
//	double perpWallDist = 0.0;

//	int stepX = 0;
//	int stepY = 0;
//	int hit = 0;
//	int side = 0;

//	int lineHeight = 0;
//	double wall_x;
//	int drawStart = 0;
//	int drawEnd = 0;*/
	x = 0;
	ft_init_cam_other(info->cam);
	while (x < info->w) {
		ft_one(info->w, x, info->cam);
/*/		cameraX = info->cam->camera_x;
//		rayDirX = info->cam->ray_dir_x;
//		rayDirY = info->cam->ray_dir_y;
//		mapX = info->cam->map_x;
//		mapY = info->cam->map_y;
//		deltaDistX = info->cam->delta_dist_x;
//		deltaDistY = info->cam->delta_dist_y;
//		stepX = info->cam->step_x;
//		sideDistX = info->cam->side_dist_x;
//		stepY = info->cam->step_y;
//		sideDistY = info->cam->side_dist_y;

//		cameraX = 2 * x / (double) info->w - 1;
//		rayDirX = info->cam->dir_x + (cameraX * info->cam->plane_x);
//		rayDirY = info->cam->dir_y + (cameraX * info->cam->plane_y);
//
//		mapX = (int) floor(info->cam->pos_x);
//		mapY = (int) floor(info->cam->pos_y);
//
//		deltaDistX = fabs(1 / rayDirX);
//		deltaDistY = fabs(1 / rayDirY);
//		hit = 0;
/		if (rayDirX < 0) {
//			stepX = -1;
//			sideDistX = (info->cam->pos_x - mapX) * deltaDistX;
//		} else {
//			stepX = 1;
//			sideDistX = (mapX + 1.0 - info->cam->pos_x) * deltaDistX;
//		}
//		if (rayDirY < 0) {
//			stepY = -1;
//			sideDistY = (info->cam->pos_y - mapY) * deltaDistY;
//		} else {
//			stepY = 1;
//			sideDistY = (mapY + 1.0 - info->cam->pos_y) * deltaDistY;
//		}

		ft_two(x, info->cam, info);
		sideDistX = info->cam->side_dist_x;
		mapX = info->cam->map_x;
		side = info->cam->side;
		sideDistY = info->cam->side_dist_y;
		mapY = info->cam->map_y;
		perpWallDist = info->cam->perp_wall_dist;

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
			if (info->arr_map[mapX + (mapY * info->max_line_len)] == '1')
				hit = 1;
		}

//
//		while (hit == 0) {
//			if (info->cam->side_dist_x < info->cam->side_dist_y) {
//				info->cam->side_dist_x += info->cam->delta_dist_x;
//				info->cam->map_x += info->cam->step_x;
//				info->cam->side = 0;
//			} else {
//				info->cam->side_dist_y += info->cam->delta_dist_y;
//				info->cam->map_y += info->cam->step_y;
//				info->cam->side = 1;
//			}
//			if (info->arr_map[info->cam->map_x + (info->cam->map_y * info->max_line_len)] == '1')
//				hit = 1;
//		}*/
		ft_two(x, info->cam, info);
/*/		sideDistX = info->cam->side_dist_x;
//		mapX = info->cam->map_x;
//		side = info->cam->side;
//		sideDistY = info->cam->side_dist_y;
//		mapY = info->cam->map_y;
//		perpWallDist = info->cam->perp_wall_dist;
//		if (info->cam->side == 0)
//			info->cam->perp_wall_dist = (info->cam->map_x - info->cam->pos_x + (1 - info->cam->step_x) / 2) / info->cam->ray_dir_x;
//		else
//			info->cam->perp_wall_dist = (info->cam->map_y - info->cam->pos_y + (1 - info->cam->step_y) / 2) / info->cam->ray_dir_y;
/

		if (side == 0)
			perpWallDist = (mapX - info->cam->pos_x + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - info->cam->pos_y + (1 - stepY) / 2) / rayDirY;


//		записывать в массив z_buff значения perpWallDist
// double ZBuffer[screenWidth];
// 	заполнять только если есть спрайты
//		if (info->count_sprites > 0)
//			info->z_buff[x] = perpWallDist;*/
		ft_three(info->h, info->cam);
/*/		lineHeight = (int) (info->h / perpWallDist);
//		drawStart = -lineHeight / 2 + info->h / 2;
//		if (drawStart < 0)
//			drawStart = 0;
//		drawEnd = lineHeight / 2 + info->h / 2;
//		if (drawEnd >= info->h)
//			drawEnd = info->h - 1;
//		drawStart = info->cam->draw_start;
//		drawEnd = info->cam->draw_end;
		// for textures needed
//		if (side == 0)
//			wall_x = info->cam->pos_y + perpWallDist * rayDirY;
//		else
//			wall_x = info->cam->pos_x + perpWallDist * rayDirX;
//		wall_x -= floor(wall_x);
		//
//
//		info->cam->side = side;
//		info->cam->perp_wall_dist =perpWallDist;
//		info->cam->side_dist_x = sideDistX;
//		info->cam->side_dist_y = sideDistY;
//		info->cam->map_x = mapX;
//		info->cam->map_y = mapY;

//		info->cam->draw_start = drawStart;
//		info->cam->draw_end = drawEnd;
//		info->cam->wall_x = wall_x;
//		info->cam->line_height = lineHeight;*/
		ft_four(x, info->cam, info);
/*
		if (side == 1 && stepY < 0)
			draw_txtr(info, info->wall_n, x, info->cam);
//			draw_txtr(info, info->wall_n, x, drawStart, drawEnd, wall_x, lineHeight);
		else if (side == 1 && stepY > 0)
			draw_txtr(info, info->wall_s, x, info->cam);
//			draw_txtr(info, info->wall_s, x, drawStart, drawEnd, wall_x, lineHeight);
		else if (side == 0 && stepX < 0)
			draw_txtr(info, info->wall_e, x, info->cam);
//			draw_txtr(info, info->wall_e, x, drawStart, drawEnd, wall_x, lineHeight);
		else if (side == 0 && stepX > 0)
			draw_txtr(info, info->wall_w, x, info->cam);
//			draw_txtr(info, info->wall_w, x, drawStart, drawEnd, wall_x, lineHeight);
//		написать функцию отрисовки потолка и пола


//		ft_draw_floor_ceiling(info, x, drawStart, drawEnd); */
		ft_draw_floor_ceiling(info, x, info->cam->draw_start, info->cam->draw_end);
		x++;
	}

	if (info->count_sprites > 0)
	{
		ft_find_dist_spr(info);
/*/}
//void 	ft_draw_sprites(t_map *info)
//{
//	создаем массив с дистанцией страйтов до игрока
// переписать в структуру для спрайтов???
// если спрайтов нет, то ничего не делаем

/*	int		spr_oder[info->count_sprites];
	double	spr_dist[info->count_sprites];
	int i = 0;
	double spr_x;
	double spr_y;

	while (i < info->count_sprites)
	{
		spr_oder[i] = i;
		spr_x = (double)(info->arr_sp[i] % info->max_line_len) + 0.5;
		spr_y = (double)(info->arr_sp[i] / info->max_line_len) + 0.5;
		spr_dist[i] = (pow((info->cam->pos_x - spr_x), 2) + pow((info->cam->pos_y - spr_y), 2));
		i++;
	}
//	можно переставлять не spr_oder, а arr_sp!!!
// и тогда убрать spr_oder совсем
	if (info->count_sprites > 0)
		ft_sort(spr_dist, spr_oder, info);

//	после сортировки, рисуем спрайты:

//	double spriteX = sp_img[spriteOrder[i]].x - posX;
//      double spriteY = sp_img[spriteOrder[i]].y - posY; */
	/*
		int ind;
		double invDet;
		double transformX;
		double transformY;
		int spriteScreenX;
		int spriteHeight;
		int drawStartY;
		int drawEndY;

		int spriteWidth;
		int drawStartX;
		int drawEndX;
		double spr_x;
		double spr_y;*/

		int i = 0;

		while (i < info->count_sprites) {
/*/			ind = info->spr_oder[i];
//			spr_x = (double) (info->arr_sp[ind] % info->max_line_len) + 0.5 - info->cam->pos_x;
//			spr_y = (double) (info->arr_sp[ind] / info->max_line_len) + 0.5 - info->cam->pos_y;
//
//			invDet = 1.0 / (info->cam->plane_x * info->cam->dir_y -
//							info->cam->dir_x * info->cam->plane_y); //required for correct matrix multiplication
//
//			transformX = invDet * (info->cam->dir_y * spr_x - info->cam->dir_x * spr_y);
//			transformY = invDet * (-info->cam->plane_y * spr_x + info->cam->plane_x *
//																 spr_y); //this is actually the depth inside the screen, that what Z is in 3D
//
//			spriteScreenX = (int) ((info->w / 2) * (1 + transformX / transformY));
//
			//calculate height of the sp_img on screen
//			spriteHeight = abs((int) (info->h /
//									  (transformY))); //using 'transformY' instead of the real distance prevents fisheye
			//calculate lowest and highest pixel to fill in current stripe
//			drawStartY = -spriteHeight / 2 + info->h / 2;
//			if (drawStartY < 0)
//				drawStartY = 0;
//			drawEndY = spriteHeight / 2 + info->h / 2;
//			if (drawEndY >= info->h)
//				drawEndY = info->h - 1;

			//calculate width of the sp_img
//			spriteWidth = abs((int) (info->h / (transformY)));
//			drawStartX = -spriteWidth / 2 + spriteScreenX;
//			if (drawStartX < 0)
//				drawStartX = 0;
//			drawEndX = spriteWidth / 2 + spriteScreenX;
//			if (drawEndX >= info->w)
//				drawEndX = info->w - 1; */
			ft_calc_spr(info, info->sprites, info->cam, info->spr_oder[i]);
			i++;
			if (info->sprites->draw_start_x >= info->sprites->draw_end_x)
				continue;

			ft_draw_spr(info, info->sprites, info->sp_img->width,  info->sp_img->height);
		/*	int stripe;
			int texX;
			int texWidth = 64; //размер текстуры
			int texHeight = 64;
			//loop through every vertical stripe of the sp_img on screen
			stripe = info->sprites->draw_start_x;
			int clr;
			int d;
			int texY;
			int y;
			while (stripe < info->sprites->draw_end_x) {
				texX = (int) (256 * (stripe - (-info->sprites->sprite_width / 2 + info->sprites->sprite_screen_x)) * texWidth / info->sprites->sprite_width) / 256;
				//the conditions in the if are:
				//1) it's in front of camera plane so you don't see things behind you
				//2) it's on the screen (left)
				//3) it's on the screen (right)
				//4) ZBuffer, with perpendicular distance
				if (info->sprites->transform_y > 0 && stripe > 0 && stripe < info->w &&
						info->sprites->transform_y < info->z_buff[stripe]) {
					for (y = info->sprites->draw_start_y; y < info->sprites->draw_end_y; y++) //for every pixel of the current stripe
					{
						d = (y) * 256 - info->h * 128 + \
								info->sprites->sprite_height * 128; //256 and 128 factors to avoid floats
						texY = ((d * texHeight) / info->sprites->sprite_height) / 256;
//					clr = texture[sp_img[spriteOrder[i]].texture][texWidth * texY + texX]; //get current color from the texture
						clr = get_pixel(info->sp_img, texX, texY);
//		my_mlx_pixel_put(info, x, y0, \
//					add_shade(0.2, texture_pixel));
						if ((clr & 0x00FFFFFF) != 0)
							my_mlx_pixel_put(info, stripe, y, add_shade(0.2, clr));
//						buffer[y][stripe] = clr; //paint pixel if it isn't black, black is the invisible color
					}
				}
				stripe++;
			} */

		}
	}
// для отладки
//	i = 0;
//	printf("after sort \n");
//	while (i < info->count_sprites) {
//		printf("%f | ", spr_dist[i]);
//		printf("%d | ", spr_oder[i]);
//		i++;
//	}

}

void 	ft_render(t_map *info)
{
	ft_draw(info);
	mlx_put_image_to_window(info->mlx, info->win, info->img, 0, 0);
	mlx_destroy_image(info->mlx, info->img);
	mlx_loop_hook(info->mlx, ft_render_next, info);
	mlx_hook(info->win, KEYPRESS, KeyPressMask, ft_key_press, info);
	mlx_hook(info->win, KEYRELEASE, KeyReleaseMask, ft_key_release, info);
	mlx_hook(info->win, DestroyNotify, StructureNotifyMask, ft_close, info);
//	mlx_hook(info->win, KEYPRESS, KeyPressMask, ft_close, info);
	mlx_loop(info->mlx);
}

void 	ft_color_wall(int side, int stepX, int stepY, t_map *info)
{
//	info->color_wall = 0x00FF00;
	if (side == 1)
	{
		if (stepY < 0)
			info->color_wall = 0x3088AA; //north
		else //if (stepY < 0)
			info->color_wall = 0xAA70AA; // south
	}
	else //if (side == 0)
	{
		if (stepX < 0)
			info->color_wall = 0x550000; //	east
		else //if (stepX > 0)
			info->color_wall = 0x110455; //	west
	}
}

