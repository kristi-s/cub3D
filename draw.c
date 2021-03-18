/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: droslyn <droslyn@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:22:59 by droslyn           #+#    #+#             */
/*   Updated: 2021/03/19 00:21:12 by droslyn          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	ft_calc_param_ray(int w, int x, t_cam *cam)
{
	cam->camera_x = 2 * x / (double)w - 1;
	cam->ray_dir_x = cam->dir_x + (cam->camera_x * cam->plane_x);
	cam->ray_dir_y = cam->dir_y + (cam->camera_x * cam->plane_y);
	cam->map_x = (int)floor(cam->pos_x);
	cam->map_y = (int)floor(cam->pos_y);
	cam->delta_dist_x = fabs(1 / cam->ray_dir_x);
	cam->delta_dist_y = fabs(1 / cam->ray_dir_y);
	cam->step_x = 1;
	if (cam->ray_dir_x < 0)
	{
		cam->step_x = -1;
		cam->side_dist_x = (cam->pos_x - cam->map_x) * cam->delta_dist_x;
	}
	else
		cam->side_dist_x = (cam->map_x + 1.0 - cam->pos_x) * cam->delta_dist_x;
	cam->step_y = 1;
	if (cam->ray_dir_y < 0)
	{
		cam->step_y = -1;
		cam->side_dist_y = (cam->pos_y - cam->map_y) * cam->delta_dist_y;
	}
	else
		cam->side_dist_y = (cam->map_y + 1.0 - cam->pos_y) * cam->delta_dist_y;
}

void	ft_find_wall(t_cam *cam, t_map *info, int hit)
{
	hit = 0;
	while (hit == 0)
	{
		if (cam->side_dist_x < cam->side_dist_y)
		{
			cam->side_dist_x += cam->delta_dist_x;
			cam->map_x += cam->step_x;
			cam->side = 0;
		}
		else
		{
			cam->side_dist_y += cam->delta_dist_y;
			cam->map_y += cam->step_y;
			cam->side = 1;
		}
		if (info->arr_map[cam->map_x + (cam->map_y * \
											info->max_line_len)] == '1')
			hit = 1;
	}
}

void	ft_calc_perp_and_param_line(int x, int h, t_cam *cam, t_map *info)
{
	if (cam->side == 0)
		cam->perp_wall_dist = (cam->map_x - cam->pos_x + (1 - cam->step_x) / \
														2) / cam->ray_dir_x;
	else
		cam->perp_wall_dist = (cam->map_y - cam->pos_y + (1 - cam->step_y) / \
														2) / cam->ray_dir_y;
	if (info->count_sprites > 0)
		info->z_buff[x] = cam->perp_wall_dist;
	cam->line_height = (int)(h / cam->perp_wall_dist);
	cam->draw_start = -(cam->line_height) / 2 + h / 2;
	if (cam->draw_start < 0)
		cam->draw_start = 0;
	cam->draw_end = cam->line_height / 2 + h / 2;
	if (cam->draw_end >= h)
		cam->draw_end = h - 1;
}

void	ft_take_line_from_pic(int x, t_cam *cam, t_map *info)
{
	if (cam->side == 0)
		cam->wall_x = cam->pos_y + cam->perp_wall_dist * cam->ray_dir_y;
	else
		cam->wall_x = cam->pos_x + cam->perp_wall_dist * cam->ray_dir_x;
	cam->wall_x -= floor(cam->wall_x);
	if (cam->side == 1 && cam->step_y < 0)
		ft_creat_txtr_wall(info, info->wall_n, x, cam);
	else if (cam->side == 1 && cam->step_y > 0)
		ft_creat_txtr_wall(info, info->wall_s, x, cam);
	else if (cam->side == 0 && cam->step_x < 0)
		ft_creat_txtr_wall(info, info->wall_e, x, cam);
	else if (cam->side == 0 && cam->step_x > 0)
		ft_creat_txtr_wall(info, info->wall_w, x, cam);
}
