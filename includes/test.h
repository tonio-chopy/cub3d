#ifndef TEST_H
# define TEST_H

# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include "../libft/includes/libft.h"
# include "../mlx/mlx.h"

# define WIN_W 640
# define WIN_H 360
# define MINIMAP_SIZE 200

# define RED 0x00FF0000
# define L_RED 0xAAFF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define BLACK 0x00000000

# define MAP_EMPTY BLUE
# define MAP_WALL GREEN
# define MAP_OUT BLACK

# define E_WALL '1'
# define E_INSIDE '0'
# define E_EMPTY ' '
# define E_NORTH 'N'
# define E_SOUTH 'S'
# define E_WEST 'W'
# define E_EAST 'E'

typedef struct s_point
{
	int	x;
	int	y;
	float xf;
	float yf;
}	t_point;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	t_point	*location;
}	t_img;

typedef struct s_map
{
	int				width;
	int				heigth;
	int				nb_elems;
	char			*elems;
	unsigned int	ceiling_color;
	unsigned int	floor_color;
	char			*NOpath;
	char			*SOpath;
	char			*WEpath;
	char			*EApath;
	char			player_orientation;
	int				player_pos;
}	t_parsed_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_minimap
{
	int		max_pixels;
	float	tilesize;
	t_img	*map;
	t_img	*player;
}	t_minimap;

typedef struct s_data
{
	t_mlx			*mlx;
	t_parsed_map	*parsed_map;
	t_minimap		*minimap;
	t_point			*dir_vector;
	t_point			*player_pos;
	char			debug;
}	t_data;

typedef enum e_shape
{
	LINE,
	TRIANGLE,
	RECTANGLE,
	CIRCLE
}	t_shapetype;

typedef struct s_shape
{
	t_shapetype type;
	t_img		*img;
	t_point		*start;
} t_shape;

// mlx
t_mlx	*init_mlx( void );
t_img	*cub_init_img(t_data *data, int width, int height, t_point *location);
int		cub_refresh(void *param);

// utils
int		rgb_to_int(double r, double g, double b);

// utils math
float   to_rad(int degrees);

// draw

void	cub_put_pix_to_img(t_img *img, int x, int y, unsigned int color);
void	cub_drawLine(t_img *img, t_point *from, t_point *to);
void	cub_draw_rect(t_img *img, t_point *from, int w, int h, unsigned int color);
void	cub_drawLine_angle(t_img *img, t_point *from, t_point *norm_vector, int degrees, float len);
void	cub_draw_cone(t_img *img, t_point *from, t_point *norm_vector, int degrees, int bisectlen);
t_point	*init_point(int x, int y);
t_point	*init_pointf(float x, float y);

// minimap
t_point	*get_coord_from_index(t_parsed_map *map, t_minimap *mini, int index);
void	cub_draw_minimap(t_data *data);
void    cub_draw_player(t_data *data);
void	init_dir_vector(t_data *data);

// errors
void    handle_fatal(t_data *data, char *custom_msg);

// clean
void	clean2d(void **array, int size, unsigned int bitmask, bool freeArr);
void	clean_mlx_and_img(t_mlx *mlx, t_img *main_img);
void	clean_data(t_data *data);

// hooks
# define K_ESCAPE 65307
# define K_LEFT 65361
# define K_UP 65362
# define K_RIGHT 65363
# define K_DOWN 65364
# define K_W 119
# define K_A 97
# define K_S 115
# define K_D 100

int		handle_no_event(void *param);
int		handle_keypress(int key, void *param);
int		handle_keyrelease(int key, void *param);

#endif
