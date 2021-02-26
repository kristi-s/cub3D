#include "cub3D.h"

static int 	ft_contents_of_line(char *line, t_map *info, char *content)
{
	int		i;

	i = 0;
	info->count_line++;
	if (ft_strlen(line) > info->max_line_len)
		info->max_line_len = ft_strlen(line);
	while(line[i] != '\0' && ft_strchr(content, line[i]))
	{
		if (ft_isalpha(line[i]))
		{
			if (info->pos_pl == 0)
			{
				info->pos_pl = line[i];
				info->cam = set_pos_player(i, info->count_line, info->pos_pl);
			}
			else
				ft_error("Error map: more than one position player\n");
		}
		i++;
	}
	if (line[i] == '\0')
		return (1);
	return (0);
}

void	ft_copy_map(char *line, t_map *info)
{
	t_list	*newlist;
	char 	*copy_line;

	if (!(copy_line = ft_strdup(line)))
		ft_error("Error memory allocation\n");
	if (!(newlist = ft_lstnew(copy_line)))
		ft_error("Error memory allocation\n");
	if (!info->start_row)
	{
		if (ft_contents_of_line(line, info, "1 ") == 1)
			info->start_row = newlist;
		else
			ft_error("Error map: not valid first line of map\n");
	}
	else
	{
		if (ft_contents_of_line(line, info, "012NSWE ") == 1)
			ft_lstadd_back(&info->last_row, newlist);
		else
			ft_error("Error map: not valid simbol in line of map\n");
	}
	info->last_row = newlist;
}

static void 	ft_fill_array(t_map *info, int i, int count)
{
	t_list		*ptr_line;

	while (count < info->max_line_len)
		info->arr_map[count++] = '1';
	ptr_line = info->start_row;
	while(ptr_line != NULL)
	{
		while(((char *)ptr_line->content)[i] != '\0')
		{
			info->arr_map[count] = ((char *)ptr_line->content)[i];
			i++;
			count++;
		}
		while (i < info->max_line_len)
		{
			info->arr_map[count] = ' ';
			i++;
			count++;
		}
		ptr_line = ptr_line->next;
		i = 0;
	}
}

void	ft_create_arr_map(t_map *info)
{
	unsigned int	size_arr;

	info->count_line++;
	size_arr = info->max_line_len * info->count_line;
	if (!(info->arr_map = malloc(sizeof(char) * size_arr)))
		ft_error("Error memory allocation\n");
	ft_fill_array(info, 0, 0);
	ft_valid_map(info);
	if (info->count_sprites > 0)
		ft_count_sprite(info);
}
