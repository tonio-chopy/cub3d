#include <test.h>

int mapX = 8;
int mapY = 8;
int mapNb = 64;
int map[] =
{
	1,1,1,1,1,1,1,1,\
	1,0,0,0,0,0,0,1,\
	1,0,0,0,0,0,0,1,\
	1,0,0,0,0,0,0,1,\
	1,0,0,0,0,0,0,1,\
	1,0,0,0,0,0,0,1,\
	1,0,0,0,0,0,0,1,\
	1,1,1,1,1,1,1,1,\
};

void drawMap2D()
{
	int x;
	int y;
	// int xo;
	// int yo;

	y = 0;
	while (y < mapY)
	{
		x = 0;
		while (x < mapX)
		{
			x++;
		}
		y++;
	}
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bpp / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1024, 768, "Test");
	img.img = mlx_new_image(mlx, 1024, 768);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
