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

//убрать def и поменять в инитах и вызове ф-ции
#define 	WAY_T_N "../txtr6.xpm"
#define		WAY_T_S "../pink.xpm"
#define		WAY_T_E "../green2.xpm"
#define		WAY_T_W "../blue.xpm"

// Resolution:
// id: R // x render size // y render size
// North texture:
// NO ./path_to_the_north_texture
// аналогично остальные: SO, WE, EA;
// Sprite texture id: S;
// Floor color:
// identifier: F  //  R,G,B colors in range [0,255]: 0, 255, 255
// Ceilling color: аналогично; id: C;
typedef struct s_cam {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double 	plane_x;
	double 	plane_y;
}			t_cam;

typedef struct	s_data {
	void *img;
	char *addr; //pointer to pixels array
	int bits_per_pixel; //32 bit
	int line_length; //width
	int endian;
	int width;
	int height;
}				t_data;

typedef struct		s_map
{
	char 			*file;
	int 			resolution_x;
	int 			resolution_y;
	char			*north_txtr;
	char			*south_txtr;
	char			*west_txtr;
	char			*east_txtr;
	char			*sprite_txtr;
	unsigned int 	floor_color;
	unsigned int 	ceilling_color;
	unsigned int	count_line_in_map;
	unsigned int 	max_line_len;
	unsigned int 	count_sprites;
	t_list			*start_row;
	t_list 			*last_row;
	char 			position_player;
	char 			*arr_map;
	t_cam			*cam;
	t_data			*wall_n;
	t_data			*wall_s;
	t_data			*wall_e;
	t_data			*wall_w;
	t_data			*sprite;
	int 		color_wall;
	int 		key[6][2];

	void    *mlx;
	void    *win;
	void 	*img;
	char 	*addr; //pointer to pixels array
	int 	bits_per_pixel; //32 bit
	int 	line_length; //width
	int 	endian;
}					t_map;
// key[8]: 0 = A; 1 = S; 2 = D; 3 = W; 4 = left; 5 = right; 6 = up; down = 7;

int		ft_isspace(char c);
void 	my_mlx_pixel_put(t_map *map_info, int x, int y, int color);
void	ft_read_map(t_map *map_info);
void	ft_init_info(t_map	*map_info);
void 	draw_ver_line(t_map *map_info, int x, int y0, int y1);
int		ft_copy_map(char *line, t_map *map_info);
int 	ft_contents_of_line(char *line, t_map *map_info, char *content);
void	ft_create_arr_map(t_map *map_info);
t_cam 	*set_pos_player(unsigned int p_x, unsigned int p_y, char way_player); ///?????
int 	ft_close(int keycode, t_map *map_info);
int 	ft_key_press(int keycode, t_map *map_info);
int 	ft_key_release(int keycode, t_map *map_info);
int     ft_render_next(t_map *map_info);
void 	ft_draw(t_map *map_info);
void 	ft_render(t_map *map_info);
//t_data		*ft_paint_texture(char *file, void *ptr_mlx);
void		ft_paint_texture(t_map *map_info);
void 	draw_txtr(t_map *map_info, t_data *txtr, int x, int y0, int y1, double wall_x, int lineHeight);
void 	ft_draw_floor_ceiling(t_map *map_info, int x, int y1, int y2);

// ft_valid_map можно сделать воид?
void	ft_valid_map(t_map *map_info);
void	ft_puterror(void);
void	ft_puterror_mem(void);
//void	ft_puterr_clean(char *arr);
void	ft_error(char *str_err);

#endif
