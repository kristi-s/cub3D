#ifndef CUB3D_CUB3D_H
# define CUB3D_CUB3D_H
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
#define KEYPRESS 2
#define KEYRELEASE 3
#define DestroyNotify 17
#define KeyPressMask (1L<<0)
#define KeyReleaseMask (1L<<1)
#define StructureNotifyMask (1L<<17)
#define KEY_ESC 53
#define KEY_A 0
#define KEY_S 1
#define KEY_D 2
#define KEY_W 13
#define KEY_LEFT 123
#define KEY_RIGTH 124

#define MOVE_SPEED 0.1
#define ROTATION 0.05
#define FOV	0.66

#define BITMAPFILEHEADER_SIZE 14
#define BITMAPINFO_SIZE 40
#define ALLBMPHEADER 54
#define PMOD 0644
#define FILE_BMP "cub3D.bmp"




// Resolution:
// id: R // x render size // y render size
// North texture:
// NO ./path_to_the_north_texture
// аналогично остальные: SO, WE, EA;
// Sprite texture id: S;
// Floor color:
// identifier: F  //  R,G,B colors in range [0,255]: 0, 255, 255
// Ceilling color: аналогично; id: C;

typedef struct	s_move {
	double		delta_x;
	double		delta_y;
	double		new_x;
	double		new_y;
	int			dir;
}				t_move;

typedef struct s_sprt {
	double	x;
	double	y;
	double	inv_det;
	double	transform_x;
	double	transform_y;
	int		sprite_screen_x;
	int		sprite_height;
	int		draw_start_y;
	int		draw_end_y;
	int		sprite_width;
	int		draw_start_x;
	int		draw_end_x;
	int		txtr_x;
	int		txtr_y;
	int		color;
	int		d;
}			t_sprt;

typedef struct s_cam {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double 	plane_x;
	double 	plane_y;

	double camera_x;
	double ray_dir_x;
	double ray_dir_y;
	int		map_x;
	int		map_y;
	double delta_dist_x;
	double delta_dist_y;
	double side_dist_x;
	double side_dist_y;
	double perp_wall_dist;
	int step_x;
	int step_y;
	int side;
	int line_height;
	int draw_start;
	int draw_end;
	double wall_x;
}			t_cam;

typedef struct	s_data {
	void *img;
	char *addr; //pointer to pixels array
	int bits_per_pixel; //32 bit
	int line_length; //width
	int endian;
	int width;
	int height;
	double		step;
	double  pos;
	int x;
	int y;
}				t_data;

typedef struct		s_map
{
	char 			*file;
	unsigned int	flag_save;
	int 			w; // resolution x
	int 			h; // resolution y
	char			*north_txtr;
	char			*south_txtr;
	char			*west_txtr;
	char			*east_txtr;
	char			*sprite_txtr;
	unsigned int 	floor_color;
	unsigned int 	ceiling_color;
	unsigned int	count_line;
	unsigned int 	max_line_len;
	unsigned int 	count_sprites;
	int				*arr_sp;
	double			*z_buff;  // нужен ли тут??
	t_list			*start_row;
	t_list 			*last_row;
	char 			pos_pl;
	char 			*arr_map;
	t_cam			*cam;
	t_data			*wall_n;
	t_data			*wall_s;
	t_data			*wall_e;
	t_data			*wall_w;
	t_data			*sp_img;
	int 		color_wall; //?
	int 		key[6][2];

	void    *mlx;
	void    *win;
	void 	*img;
	char 	*addr; //pointer to pixels array
	int 	bits_per_pixel; //32 bit
	int 	line_length; //width
	int 	endian;

	int		*spr_oder;
	double	*spr_dist;
	t_sprt	*sprites;
}					t_map;
// key[8]: 0 = A; 1 = S; 2 = D; 3 = W; 4 = left; 5 = right; 6 = up; down = 7;

int		ft_isspace(char c);
void 	ft_my_mlx_pixel_put(t_map *info, int x, int y, int color);
void	ft_read_map(t_map *info);
void	ft_init_info(t_map	*info);
//void 	draw_ver_line(t_map *info, int x, int y0, int y1);
void		ft_copy_map(char *line, t_map *info);
//int 	ft_contents_of_line(char *line, t_map *info, char *content);
void	ft_create_arr_map(t_map *info);
t_cam 	*ft_set_pos_player(unsigned int p_x, unsigned int p_y, char way_player); ///?????
int 	ft_close(void);
int 	ft_key_press(int keycode, t_map *info);
int 	ft_key_release(int keycode, t_map *info);
void	ft_choose_action(int i, t_map *info);
//int     ft_render_next(t_map *info);
void 	ft_calc(t_map *info, t_cam *cam, unsigned int i, int x);
void 	ft_render(t_map *info);
//t_data		*ft_paint_texture(char *file, void *ptr_mlx);
void		ft_paint_texture(t_map *info);
void 	ft_creat_txtr_wall(t_map *info, t_data *txtr, int x, t_cam *cam);
void 	ft_draw_floor_ceiling(t_map *info, int x, int y1, int y2);

void	ft_init_cam_other(t_cam *cam);
void 	ft_calc_param_ray(int w, int x, t_cam *cam);
void 	ft_find_wall(t_cam *cam, t_map *info, int hit);
void 	ft_calc_perp_and_param_line(int x, int h, t_cam *cam, t_map *info);
void 	ft_take_line_from_pic(int x, t_cam *cam, t_map *info);
void 	ft_find_dist_spr(t_map *info);
void 	ft_calc_spr(t_map *info, t_sprt *spr, t_cam *cam, int ind);
void 	ft_draw_spr(t_map *info, t_sprt *spr, int txt_w, int txt_h);

void	ft_count_sprite(t_map *info);

void	ft_valid_map(t_map *info);

//void	ft_puterror_mem(void);
void	ft_error(char *str_err);

void	ft_sort(t_map *info);


int			ft_get_pxl_clr(t_data *txtr, int x, int y);
void		ft_make_screenshot(t_map *info);

#endif
