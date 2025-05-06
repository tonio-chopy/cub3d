#ifndef TEST_H
# define TEST_H

# include <stdlib.h>
# include <math.h>
# include <mlx.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_data;

#endif
