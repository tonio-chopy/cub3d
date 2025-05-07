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

void	cub_put_pix_to_img(t_img *img, int x, int y, unsigned int color)
{
	char	*pixel;

	// if (!img || x < 0 || y < 0 || x >= img->width || y >= img->height)
	// 	return ;
	pixel = img->addr + (int) (y * img->line_length + x * (img->bpp / 8));
	// if (img->bpp == 32)
		*(unsigned int *) pixel = color;
	// else if (img->bpp == 24)
    // {
    //     /* Gestion des formats 24 bits (3 bytes par pixel) */
    //     if (img->endian == 0) /* little endian */
    //     {
    //         pixel[0] = (color) & 0xFF;        /* Bleu */
    //         pixel[1] = (color >> 8) & 0xFF;   /* Vert */
    //         pixel[2] = (color >> 16) & 0xFF;  /* Rouge */
    //     }
    //     else /* big endian */
    //     {
    //         pixel[0] = (color >> 16) & 0xFF;  /* Rouge */
    //         pixel[1] = (color >> 8) & 0xFF;   /* Vert */
    //         pixel[2] = (color) & 0xFF;        /* Bleu */
    //     }
    // }
    // else if (img->bpp == 16)
    // {
    //     /* Pour les formats 16 bits (high color) */
    //     *(unsigned short *)pixel = (unsigned short)color;
    // }
}

void	cub_draw_Hline(t_img *img, int fromX, int toX, int y)
{
	int	i;

	i = fromX;
	while (i < toX)
	{
		cub_put_pix_to_img(img, i, y, 0xFF0000);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	void	*mlx;
	void	*mlx_win;
	t_img	*img;

	if (!env)
		return (EXIT_FAILURE);
	(void) ac;
	(void) av;
	mlx = mlx_init();
	if (!mlx)
		return (EXIT_FAILURE);
	mlx_win = mlx_new_window(mlx, WIN_W, WIN_H, "Test");
	if (!mlx_win)
	{
		free(mlx);
		return (EXIT_FAILURE);
	}
	img =  ft_calloc(1, sizeof(t_img));
	img->img = mlx_new_image(mlx, WIN_W, WIN_H);
	if (!img->img)
		return (EXIT_FAILURE);

	int	bpp;
	int line_length;
	int	endian;
	img->addr = mlx_get_data_addr(img->img, &bpp, &line_length, &endian);
	img->bpp = bpp;
	img->line_length = line_length;
	img->endian = endian;
	img->width = WIN_W;
	img->height = WIN_H;
	// cub_put_pix_to_img(&img, 5, 5, 0xFF0000);
	cub_draw_Hline(img, 50, 500, 100);
	mlx_put_image_to_window(mlx, mlx_win, img->img, 0, 0);
	mlx_loop(mlx);
	mlx_destroy_window(mlx, mlx_win);
	mlx_destroy_display(mlx);
	free(mlx);
	free(img);
	return (EXIT_SUCCESS);
}
