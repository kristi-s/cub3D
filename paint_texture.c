#include "cub3D.h"


t_data		*ft_create_img_txtr(char *file, void *ptr_mlx)
{
	t_data *txtr;

	if (!(txtr = malloc(sizeof(t_data))))
		ft_error("Error memory allocation\n");
	txtr->img = mlx_xpm_file_to_image(ptr_mlx, file, \
							&txtr->width, &txtr->height);
	if (!txtr->img)
		ft_error("Error map: error texture\n");
	txtr->addr = mlx_get_data_addr(txtr->img, &txtr->bits_per_pixel, \
							&txtr->line_length, &txtr->endian);
	return (txtr);
}

void		ft_paint_texture(t_map *info)
{
	info->wall_n = ft_create_img_txtr(info->north_txtr, info->mlx);
	info->wall_s = ft_create_img_txtr(info->south_txtr, info->mlx);
	info->wall_e = ft_create_img_txtr(info->east_txtr, info->mlx);
	info->wall_w = ft_create_img_txtr(info->west_txtr, info->mlx);
	info->sp_img = ft_create_img_txtr(info->sprite_txtr, info->mlx);
}


int			ft_get_pixel_color(t_data *txtr, int x, int y)
{
	int		*ptr;
	int		color;

	ptr = (void *)txtr->addr + (y * txtr->line_length + x * \
												(txtr->bits_per_pixel / 8));
	color = *(int*)ptr;
	return (color);
}

void		ft_creat_txtr_wall(t_map *info, t_data *txtr, int x, t_cam *cam)
{
	int		texture_pixel;
	int		i;

	i = cam->draw_start;
	txtr->step = 1.0 * txtr->height / cam->line_height;
	txtr->pos = (cam->draw_start - info->h / 2.0 + cam->line_height / 2.0) * txtr->step;
	txtr->x = (int)(cam->wall_x * (double)txtr->width);
	while (i < cam->draw_end)
	{
		txtr->y = (int)txtr->pos & (txtr->height - 1);
		txtr->pos += txtr->step;
		texture_pixel = ft_get_pixel_color(txtr, txtr->x, txtr->y);
		ft_my_mlx_pixel_put(info, x, i, texture_pixel);
		i++;
	}
}



void 	ft_my_mlx_pixel_put(t_map *info, int x, int y, int color)
{
	char *dst;

	dst = info->addr + (y * info->line_length + x * (info->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*
void 	draw_ver_line(t_map *info, int x, int y0, int y1) {
	int color;

	color = info->color_wall;

	for (int i = y0; i <= y1; i++) {
		ft_my_mlx_pixel_put(info, x, i, color);
	}
}
*/
//	unsigned int 	floor_color;
//	unsigned int 	ceiling_color;
//draw_ver_line(map_info, x, drawStart, drawEnd);

void 	ft_draw_floor_ceiling(t_map *info, int x, int y1, int y2)
{
	int i;

	i = 0;
	while (i < y1)
	{
		ft_my_mlx_pixel_put(info, x, i, info->ceiling_color);
		i++;
	}
	i = y2 + 1;
	while (i < info->h)
	{
		ft_my_mlx_pixel_put(info, x, i, info->floor_color);
		i++;
	}
}