#ifndef TEST_H
# define TEST_H

# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include "../libft/includes/libft.h"
# include "mlx.h"

# define WIN_W 640
# define WIN_H 360
# define MINIMAP_SIZE 100

# define RED 0x00FF0000
# define L_RED 0xAAFF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF

# define MAP_EMPTY BLUE
# define MAP_WALL GREEN

# define E_WALL '1'
# define E_INSIDE '0'
# define E_EMPTY ' '
# define E_NORTH 'N'
# define E_SOUTH 'S'
# define E_WEST 'W'
# define E_EAST 'E'

typedef enum e_dir
{
	LEFT,
	UP,
	RIGHT,
	DOWN
}	t_dir;

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
	char			*elems;
	unsigned int	ceiling_color;
	unsigned int	floor_color;
	char			*NOpath;
	char			*SOpath;
	char			*WEpath;
	char			*EApath;
	int				player_pos;
}	t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;

typedef struct s_data
{
	t_mlx	*mlx;
	t_map	*map;
	t_img	*mini;
	bool	debug;
}	t_data;

typedef struct s_minimap
{
	int		max_pixels;
	float	tilesize;
	t_img	img;
}	t_minimap;

// mlx
t_mlx	*init_mlx( void );
t_img	*cub_init_img(t_mlx *mlx, int width, int height, t_point *location);
int		cub_refresh(void *param);

// utils
int		rgb_to_int(double r, double g, double b);

// draw
void	cub_put_pix_to_img(t_img *img, int x, int y, unsigned int color);
void	cub_drawLine(t_img *img, t_point *from, t_point *to);
void	cub_draw_rect(t_img *img, int xstart, int ystart, int w, int h, unsigned int color);
t_point	*init_point(int x, int y);

// minimap
void	cub_display_map(t_map *map, t_img *img, t_point *screenLocation);

// clean
void	clean2d(void **array, int size, unsigned int bitmask, bool freeArr);
void	clean_mlx_and_img(t_mlx *mlx, t_img *main_img);

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
