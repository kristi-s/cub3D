#include "cub3D.h"

// можно передавать ptr_mlx, path (путь н-р "./txtr.xpm",
// и адрес куда записать указатель на полученную структуру)
t_data		*ft_paint_texture(char *file, void *ptr_mlx)
{
	t_data  *txtr;

	if (!(txtr = malloc(sizeof(t_data))))
		exit(1); // добавить функцию ft_exit;
	txtr->img = mlx_xpm_file_to_image(ptr_mlx, file, \
							&txtr->width, &txtr->height);
   	if (!txtr->img)
		exit(1); // добавить функцию ft_exit;
	txtr->addr = mlx_get_data_addr(txtr->img, &txtr->bits_per_pixel, \
							&txtr->line_length, &txtr->endian);
	return (txtr);
}

// переименовать и переписать??
int			add_shade(double distance, int color)
{
	int		transparency;
	int		red;
	int		green;
	int		blue;

	transparency = color & 0xFF000000;
	red = color & 0x00FF0000;
	green = color & 0x0000FF00;
	blue = color & 0x000000FF;
	red = (red >> 16) * (1 - distance);
	green = (green >> 8) * (1 - distance);
	blue = blue * (1 - distance);
	red = red << 16;
	green = green << 8;
	return (transparency | red | green | blue);
}

// переименовать и переписать??
int			get_pixel(t_data *txtr, int x, int y)
{
	int		*dst;
	int		color;

	dst = (void *)txtr->addr + (y * txtr->line_length + x * \
												(txtr->bits_per_pixel / 8));
	color = *(int*)dst;
	return (color);
}


// if (sv->map.side == 1 && sv->map.step_y < 0)
// переименовать и переписать??
void				draw_txtr(t_map *map_info, t_data *txtr, int x, int y0, int y1, double wall_x, int lineHeight)
{
	int				texture_pixel;
//	int				y; = y0;

//	y = sv->draw.draw_start;
//	sv->map.tex_x = (int)(sv->map.wall_x * (double)sv->map.no_w);
//	if (sv->map.side == 1 && sv->map.ray_dir_y > 0)
//		sv->map.tex_x = sv->map.no_w - sv->map.tex_x - 1;
//	sv->map.step = 1.0 * sv->map.no_h / sv->map.line_height;
//	sv->map.tex_pos = (sv->draw.draw_start - sv->map.res_h / 2 + \
//						sv->map.line_height / 2) * sv->map.step;

	double step = 1.0 * txtr->height / lineHeight;
	double tex_pos = (y0 - map_info->resolution_y / 2 + \
						lineHeight / 2) * step;

	int tex_x = (int)(wall_x * (double)txtr->width);
	while (y0 < y1)
	{
		int tex_y = (int)tex_pos & (txtr->height - 1);
		tex_pos += step;
		texture_pixel = get_pixel(txtr, tex_x, tex_y);
		my_mlx_pixel_put(map_info, x, y0, \
					add_shade(0.2, texture_pixel));
		y0++;
	}
}



void 	my_mlx_pixel_put(t_map *map_info, int x, int y, int color) {
	char *dst;

// разобраться как должно быть
	dst = map_info->addr + (y * map_info->line_length + x * (map_info->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*
void 	draw_ver_line(t_map *map_info, int x, int y0, int y1) {
	int color;

	color = map_info->color_wall;

	for (int i = y0; i <= y1; i++) {
		my_mlx_pixel_put(map_info, x, i, color);
	}
}
*/
//	unsigned int 	floor_color;
//	unsigned int 	ceilling_color;
//draw_ver_line(map_info, x, drawStart, drawEnd);

void 	ft_draw_floor_ceiling(t_map *map_info, int x, int y1, int y2)
{
	int i;

	i = 0;
	while (i < y1)
	{
		my_mlx_pixel_put(map_info, x, i, map_info->ceilling_color);
		i++;
	}
	i = y2 + 1;
	while (i < map_info->resolution_y)
	{
		my_mlx_pixel_put(map_info, x, i, map_info->floor_color);
		i++;
	}
}