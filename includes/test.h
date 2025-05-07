#ifndef TEST_H
# define TEST_H

# include <stdlib.h>
# include <math.h>
# include "../libft/includes/libft.h"

# define WIN_W 640
# define WIN_H 360

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
}	t_point;

// utils
int rgb_to_int(double r, double g, double b);

#endif
