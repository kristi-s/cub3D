#include "cub3D.h"
//void 	ft_color_wall(int side, int stepX, int stepY, t_map *info);
// struct
//double cameraX
//	double rayDirX
//	double rayDirY
//int mapX
//int mapY
//double deltaDistX
//double deltaDistY
//double sideDistX
//double sideDistY
//double perpWallDist

void	ft_init_cam_other(t_cam *cam)
{
	cam->camera_x = 0.0;
	cam->ray_dir_x = 0.0;
	cam->ray_dir_y = 0.0;
	cam->map_x = 0;
	cam->map_y = 0;
	cam->delta_dist_x = 0.0;
	cam->delta_dist_y = 0.0;
	cam->side_dist_x = 0.0;
	cam->side_dist_y = 0.0;
	cam->perp_wall_dist = 0.0;
	cam->step_x = 0;
	cam->step_y = 0;
	cam->side = 0;
	cam->line_height = 0;
	cam->draw_start = 0;
	cam->draw_end = 0;
	cam->wall_x = 0.0;

}

void 	ft_one(int w, int x, t_cam *cam)
{ // вычисляем положение луча и направление
	cam->camera_x = 2 * x / (double)w - 1;
	cam->ray_dir_x = cam->dir_x + (cam->camera_x * cam->plane_x);
	cam->ray_dir_y = cam->dir_y + (cam->camera_x * cam->plane_y);
	cam->map_x = (int) floor(cam->pos_x);
	cam->map_y = (int) floor(cam->pos_y);
	cam->delta_dist_x = fabs(1 / cam->ray_dir_x);
	cam->delta_dist_y = fabs(1 / cam->ray_dir_y);
	if (cam->ray_dir_x < 0) {
		cam->step_x = -1;
		cam->side_dist_x = (cam->pos_x - cam->map_x) * cam->delta_dist_x;
	} else {
		cam->step_x = 1;
		cam->side_dist_x = (cam->map_x + 1.0 - cam->pos_x) * cam->delta_dist_x;
	}
	if (cam->ray_dir_y < 0) {
		cam->step_y = -1;
		cam->side_dist_y = (cam->pos_y - cam->map_y) * cam->delta_dist_y;
	} else {
		cam->step_y = 1;
		cam->side_dist_y = (cam->map_y + 1.0 - cam->pos_y) * cam->delta_dist_y;
	}
}

void 	ft_two(int x, t_cam *cam, t_map *info)
{
	int	hit;

	hit = 0;
	while (hit == 0) {
		if (cam->side_dist_x < cam->side_dist_y) {
			cam->side_dist_x += cam->delta_dist_x;
			cam->map_x += cam->step_x;
			cam->side = 0;
		} else {
			cam->side_dist_y += cam->delta_dist_y;
			cam->map_y += cam->step_y;
			cam->side = 1;
		}
		if (info->arr_map[cam->map_x + (cam->map_y * info->max_line_len)] == '1')
			hit = 1;
	}
	if (cam->side == 0)
		cam->perp_wall_dist = (cam->map_x - cam->pos_x + (1 - cam->step_x) / 2) / cam->ray_dir_x;
	else
		cam->perp_wall_dist = (cam->map_y - cam->pos_y + (1 - cam->step_y) / 2) / cam->ray_dir_y;
	if (info->count_sprites > 0)
		info->z_buff[x] = cam->perp_wall_dist;
}
//		записывать в массив z_buff значения perpWallDist
// double ZBuffer[screenWidth];
// 	заполнять только если есть спрайты



void 	ft_three(int h, t_cam *cam)
{
	cam->line_height = (int)(h / cam->perp_wall_dist);
	cam->draw_start = -(cam->line_height) / 2 + h / 2;
	if (cam->draw_start < 0)
		cam->draw_start = 0;
	cam->draw_end = cam->line_height / 2 + h / 2;
	if (cam->draw_end >= h)
		cam->draw_end = h - 1;
}

void 	ft_four(int x, t_cam *cam, t_map *info)
{
	// for textures needed
	if (cam->side == 0)
		cam->wall_x = cam->pos_y + cam->perp_wall_dist * cam->ray_dir_y;
	else
		cam->wall_x = cam->pos_x + cam->perp_wall_dist * cam->ray_dir_x;
	cam->wall_x -= floor(cam->wall_x);
	//
	if (cam->side == 1 && cam->step_y < 0)
		draw_txtr(info, info->wall_n, x, cam);
	else if (cam->side == 1 && cam->step_y > 0)
		draw_txtr(info, info->wall_s, x, cam);
	else if (cam->side == 0 && cam->step_x < 0)
		draw_txtr(info, info->wall_e, x, cam);
	else if (cam->side == 0 && cam->step_x > 0)
		draw_txtr(info, info->wall_w, x, cam);
}
/*
void 	ft_draw(t_map *info)
{
	int x;

	x = 0;
	ft_init_cam_other(info->cam);
	while (x < info->w) {
		ft_one(info->w, x, info->cam);
		ft_two(x, info->cam, info);
		ft_three(info->h, info->cam);
		ft_four(x, info->cam, info);

		ft_draw_floor_ceiling(info, x, info->cam->draw_start, info->cam->draw_end);

		x++;
	}

*/

// ft_five
/*
void 	ft_find_dist_spr(t_map *info)
{
	int i = 0;
	double spr_x;
	double spr_y;

	while (i < info->count_sprites)
	{
		spr_x = (double) (info->arr_sp[i] % info->max_line_len) + 0.5;
		spr_y = (double) (info->arr_sp[i] / info->max_line_len) + 0.5;
		info->spr_dist[i] = (pow((info->cam->pos_x - spr_x), 2) + \
								pow((info->cam->pos_y - spr_y), 2));
		i++;
	}
	ft_sort(info);
}*/

// ft_six
void 	ft_calc_spr(t_map *info, t_sprt *spr, t_cam *cam, int ind)
{
	spr->x = (double) (info->arr_sp[ind] % info->max_line_len) + 0.5 - cam->pos_x;
	spr->y = (double) (info->arr_sp[ind] / info->max_line_len) + 0.5 - cam->pos_y;
	spr->inv_det = 1.0 / (cam->plane_x * cam->dir_y - cam->dir_x * cam->plane_y);
	spr->transform_x = spr->inv_det * (info->cam->dir_y * spr->x - \
										info->cam->dir_x * spr->y);
	spr->transform_y = spr->inv_det * (-cam->plane_y * spr->x + \
										info->cam->plane_x * spr->y);
	spr->sprite_screen_x = (int)((info->w / 2) * \
							(1 + spr->transform_x / spr->transform_y));
	spr->sprite_height = abs((int)(info->h /(spr->transform_y)));
	spr->draw_start_y = -spr->sprite_height / 2 + info->h / 2;
	if (spr->draw_start_y < 0)
		spr->draw_start_y = 0;
	spr->draw_end_y = spr->sprite_height / 2 + info->h / 2;
	if (spr->draw_end_y >= info->h)
		spr->draw_end_y = info->h - 1;
	spr->sprite_width = abs((int) (info->h / (spr->transform_y)));
	spr->draw_start_x = -spr->sprite_width / 2 + spr->sprite_screen_x;
	if (spr->draw_start_x < 0)
		spr->draw_start_x = 0;
	spr->draw_end_x = spr->sprite_width / 2 + spr->sprite_screen_x;
	if (spr->draw_end_x >= info->w)
		spr->draw_end_x = info->w - 1;
}
// ft_draw_spr(info, info->sprites, info->sp_img->width, info->sp_img->height);
void 	ft_draw_spr(t_map *info, t_sprt *spr, int txt_w, int txt_h)
{
	int stripe;
//	int texX;
//	int texY;
//	int texWidth = 64; //размер текстуры
//	int texHeight = 64;
	//loop through every vertical stripe of the sp_img on screen
	stripe = spr->draw_start_x;
	int color;
	int d;
	int y;
	while (stripe < spr->draw_end_x) {
		spr->txtr_x = (int) (256 * (stripe - (-spr->sprite_width / 2 + spr->sprite_screen_x)) * \
									txt_w / spr->sprite_width) / 256;
		if (spr->transform_y > 0 && stripe > 0 && stripe < info->w &&
				spr->transform_y  < info->z_buff[stripe]) {
			y = spr->draw_start_y;
			while (y < spr->draw_end_y)
			{
				d = (y) * 256 - info->h * 128 + \
					spr->sprite_height * 128;
				spr->txtr_y = ((d * txt_h) / spr->sprite_height) / 256;
				color = get_pixel(info->sp_img, spr->txtr_x, spr->txtr_y);
				if ((color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(info, stripe, y, add_shade(0.2, color));
				y++;
			}
		}
		stripe++;
	}
}

//	создаем массив с дистанцией страйтов до игрока
// переписать в структуру для спрайтов???
// если спрайтов нет, то ничего не делаем
/*
void 	ft_draw_sprites(t_map *info) {


//	после сортировки, рисуем спрайты:

	int i = 0;
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
	double spr_y;

	while (i < info->count_sprites) {
		ft_calc_spr(info, info->sprites, info->cam, info->spr_oder[i]);


		i++;
		if (drawStartX >= drawEndX)
			continue;



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
*/
