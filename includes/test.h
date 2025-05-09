#ifndef TEST_H
# define TEST_H

# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h> // TO DELETE
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include "libft/includes/libft.h"
# include "mlx/mlx.h"

# define WIN_W 640
# define WIN_H 360
# define MIN_W 100

# define RED 0x00FF0000
# define L_RED 0xAAFF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF

# define E_WALL 1
# define E_EMPTY 0
typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_point
{
	int	x;
	int	y;
	float xf;
	float yf;
}	t_point;

typedef struct s_map
{
	int		width;
	int		heigth;
	int		*elems;
	t_point	*location;
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
}	t_data;

// mlx
t_mlx	*init_mlx( void );
t_img	*init_img(t_mlx *mlx, int width, int height);

// utils
int		rgb_to_int(double r, double g, double b);

// clean
void	clean2d(void **array, int size, unsigned int bitmask, bool freeArr);
void	clean_mlx_and_img(t_mlx *mlx, t_img *main_img);

// hooks
# define K_ESCAPE 0
int		handle_no_event(void *param);
int		handle_keypress(int key, void *param);
int		handle_keyrelease(int key, void *param);


#endif
