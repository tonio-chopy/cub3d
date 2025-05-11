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

t_mlx	*cub_init_mlx( void )
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

void	cub_clear_img(t_img *img)
{
	int	y;
	int	x;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			cub_put_pix_to_img(img, x, y, BLACK);
			x++;
		}
		y++;
	}
}

void	update_rotation(t_data *data)
{
	if (data->rotates_left)
	{
		ft_rotate_vector(data->dir_vector, 0.5);
		ft_normalize_vector(data->dir_vector);
	}
}

int cub_refresh(void *param)
{
	t_data	*data;

	data = (t_data *) param;
	update_rotation(data);
	cub_clear_img(data->minimap->map);
	cub_draw_minimap(data);
	cub_draw_player(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->minimap->map->img, data->minimap->map->location->x, data->minimap->map->location->y);
	return (EXIT_SUCCESS);
}