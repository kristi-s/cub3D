#include "cub3D.h"

void	ft_count_sprite(t_map *info)
{
	int 	i;
	int		ind;

	i = 0;
	ind = 0;
	if (!(info->arr_sp = malloc(info->count_sprites * sizeof(int))))
		ft_error("Error memory allocation\n");
	if (!(info->spr_dist = malloc(info->count_sprites * sizeof(double))))
		ft_error("Error memory allocation\n");
	if (!(info->spr_oder = malloc(info->count_sprites * sizeof(int))))
		ft_error("Error memory allocation\n");
	if (!(info->sprites = malloc(sizeof(t_sprt))))
		ft_error("Error memory allocation\n");
	while (i < (info->max_line_len * info->count_line))
	{
		if (info->arr_map[i] == '2')
		{
			info->arr_sp[ind] = i;
			ind++;
		}
		i++;
	}
	if (!(info->z_buff = malloc(info->w * sizeof(double))))
		ft_error("Error memory allocation\n");
}


//сортирует от дальнего до ближнего
void	ft_sort(t_map *info)
{
	int i;
	int j = 0;
	double tmp;
	int temp_i;

	while(j < info->count_sprites - 1)
	{
		i = 0;
		while (i < info->count_sprites - j - 1)
		{
			if (info->spr_dist[i] < info->spr_dist[i + 1])
			{
				tmp = info->spr_dist[i];
				info->spr_dist[i] = info->spr_dist[i + 1];
				info->spr_dist[i + 1] = tmp;
				temp_i = info->spr_oder[i];
				info->spr_oder[i] = info->spr_oder[i + 1];
				info->spr_oder[i + 1] = temp_i;
			}
			i++;
		}
		j++;
	}
}

void 	ft_find_dist_spr(t_map *info)
{
	int i = 0;
	double spr_x;
	double spr_y;

	while (i < info->count_sprites)
	{
		info->spr_oder[i] = i;
		spr_x = (double) (info->arr_sp[i] % info->max_line_len) + 0.5;
		spr_y = (double) (info->arr_sp[i] / info->max_line_len) + 0.5;
		info->spr_dist[i] = (pow((info->cam->pos_x - spr_x), 2) + \
								pow((info->cam->pos_y - spr_y), 2));
		i++;
	}
	ft_sort(info);
}