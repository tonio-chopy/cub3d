#include "../includes/test.h"
#include "../mlx/mlx.h"

// int mapX = 8;
// int mapY = 8;
// int mapNb = 64;
// int map[] =
// {
// 	1,1,1,1,1,1,1,1,\
// 	1,0,0,0,0,0,0,1,\
// 	1,0,0,0,0,0,0,1,\
// 	1,0,0,0,0,0,0,1,\
// 	1,0,0,0,0,0,0,1,\
// 	1,0,0,0,0,0,0,1,\
// 	1,0,0,0,0,0,0,1,\
// 	1,1,1,1,1,1,1,1,\
// };

// void drawMap2D()
// {
// 	int x;
// 	int y;
// 	// int xo;
// 	// int yo;

// 	y = 0;
// 	while (y < mapY)
// 	{
// 		x = 0;
// 		while (x < mapX)
// 		{
// 			x++;
// 		}
// 		y++;
// 	}
// }

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_img	img;

	mlx = mlx_init();
	if (!mlx)
		return (EXIT_FAILURE);
	mlx_win = mlx_new_window(mlx, WIN_W, WIN_H, "Test");
	if (!mlx_win)
	{
		free(mlx);
		return (EXIT_FAILURE);
	}
	img.img = mlx_new_image(mlx, WIN_W, 1080);
	mlx_pixel_put(mlx, mlx_win, 5, 5, 0xFF0000);
	// mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
	mlx_destroy_window(mlx, mlx_win);
	mlx_destroy_display(mlx);
	free(mlx);
}
