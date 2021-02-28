#include "cub3D.h"


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

void 	ft_calc(t_map *info)
{
	int x;
	int i;

	x = 0;
	ft_init_cam_other(info->cam);
	while (x < info->w) {
		ft_calc_param_ray(info->w, x, info->cam);
		ft_find_wall_calc_perp(x, info->cam, info);
		ft_calc_param_line(info->h, info->cam);
		ft_take_line_from_pic(x, info->cam, info);
		ft_draw_floor_ceiling(info, x, info->cam->draw_start, info->cam->draw_end);
		x++;
	}
	if (info->count_sprites > 0)
	{
		ft_find_dist_spr(info);
		i = 0;
		while (i < info->count_sprites)
		{
			ft_calc_spr(info, info->sprites, info->cam, info->spr_oder[i]);
			i++;
			if (info->sprites->draw_start_x >= info->sprites->draw_end_x)
				continue;
			ft_draw_spr(info, info->sprites, info->sp_img->width,  info->sp_img->height);
		}
	}
}

void 	ft_render(t_map *info)
{
	ft_calc(info);
	mlx_put_image_to_window(info->mlx, info->win, info->img, 0, 0);
	mlx_destroy_image(info->mlx, info->img);
	mlx_loop_hook(info->mlx, ft_render_next, info);
	mlx_hook(info->win, KEYPRESS, KeyPressMask, ft_key_press, info);
	mlx_hook(info->win, KEYRELEASE, KeyReleaseMask, ft_key_release, info);
	mlx_hook(info->win, DestroyNotify, StructureNotifyMask, ft_close, info);
	mlx_loop(info->mlx);
}

