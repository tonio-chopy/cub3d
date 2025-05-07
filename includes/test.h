#ifndef TEST_H
# define TEST_H

# include <stdlib.h>
# include <math.h>
# include "../libft/includes/libft.h"

# define WIN_W 640
# define WIN_H 360

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
	int	width;
	int	heigth;
	int	*elems;
}	t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
}	t_mlx;


// utils
int rgb_to_int(double r, double g, double b);

#endif
