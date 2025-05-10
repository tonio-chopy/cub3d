#include "test.h"

static void	update_img_info(t_img *img, int bpp, int line_length, int endian)
{
	img->bpp = bpp;
	img->line_length = line_length;
	img->endian = endian;
}

t_img	*cub_init_img(t_data *data, int width, int height, t_point *location)
{
	t_img	*img;
	int		bpp;
	int		line_length;
	int		endian;

	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(data->mlx->mlx, width, height);
	if (!img->img)
	{
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &bpp, &line_length, &endian);
	if (!img->addr)
	{
		free(img->img);
		free(img);
		return (NULL);
	}
	update_img_info(img, bpp, line_length, endian);
	img->width = width;
	img->height = height;
	img->location = location;
	return (img);
}

t_mlx	*init_mlx( void )
{
	t_mlx	*mlx;
	void	*mlxptr;
	void	*mlxwin;

	mlx = ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlxptr = mlx_init();
	if (!mlxptr)
	{
		free(mlx);
		return (NULL);
	}
	mlx->mlx = mlxptr;
	mlxwin = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "Test");
	if (!mlxwin)
	{
		free(mlx);
		return (NULL);
	}
	mlx->win = mlxwin;
	return (mlx);
}

int cub_refresh(void *param)
{
	t_data	*data;

	data = (t_data *) param;
	cub_draw_minimap(data);
	cub_draw_player(data);
	return (EXIT_SUCCESS);
}