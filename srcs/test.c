#include "../includes/test.h"
#include "../mlx/mlx.h"

void	cub_put_pix_to_img(t_img *img, int x, int y, unsigned int color)
{
	char	*pixel;

	pixel = img->addr + (int) (y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *) pixel = color;
}
void	cub_drawLine(t_img *img, t_point *from, t_point *to)
{
	int		steps;
	t_point	delta;
	t_point	inc;
	t_point	draw;
	int		i;

	delta.x = to->x - from->x;
	delta.y = to->y - from->y;
	if (abs(delta.x) > abs(delta.y))
		steps = abs(delta.x);
	else
		steps = abs(delta.y);
	inc.xf = delta.x / (float) steps;
	inc.yf = delta.y / (float) steps;
	draw.xf = (float) from->x;
	draw.yf = (float) from->y;
	i = 0;
	while (i < steps)
	{
		cub_put_pix_to_img(img, round(draw.xf), round(draw.yf), L_RED);
		draw.xf += inc.xf;
		draw.yf += inc.yf;
		i++;
	}
}

// starting from topleftmost corner
void	cub_draw_rect(t_img *img, int xstart, int ystart, int w, int h, unsigned int color)
{
	int x;
	int	y;

	x = xstart;
	y = ystart;
	while (y < ystart + h)
	{
		while (x < xstart + w)
		{
			cub_put_pix_to_img(img, x, y, color);
			x++;
		}
		y++;
	}
}

t_img	*init_img(t_mlx *mlx, int width, int height)
{
	t_img	*img;
	int		bpp;
	int		line_length;
	int		endian;

	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(mlx->mlx, width, height);
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
	img->bpp = bpp;
	img->line_length = line_length;
	img->endian = endian;
	img->width = width;
	img->height = height;
	return (img);
}

void	draw_map_elem(t_img *img, int index, int tile_type, t_point *screenLocationStart, int square_size, t_map *map)
{
	int	x;
	int	y;
	int	color;

	color = BLUE;
	if (tile_type == 1)
		color = GREEN;
	x = screenLocationStart->x + (index % map->width) * square_size;
	y = screenLocationStart->y + (index % map->heigth) * square_size;
	cub_draw_rect(img, x, y, square_size, square_size, color);
}

void	display_map(t_map *map, t_img *img, t_point *screenLocation)
{
	int x;
	int y;
	int	map_value;
	int	square_size;

	if (map->heigth > map->width)
	{
		square_size = 32 / map->heigth;
	}
	else
	{
		square_size = 32 / map->width;
	}
	y = 1;
	while (y <= map->heigth)
	{
		x = 1;
		while (x <= map->width)
		{
			map_value = map->elems[y * x - 1];
			draw_map_elem(img, x * y - 1, map_value, screenLocation, square_size, map);
			x++;
		}
		y++;
	}

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

void	ft_cpy_arr(int *arrFrom, int *arrTo, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		arrTo[i] = arrFrom[i];
		i++;
	}
}

void	test_display_map(t_img *main_img)
{
	t_map	*map;
	t_point	map_location;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return ;
	int mapElems[] =
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
	map->elems = ft_calloc(64, sizeof(int));
	if (!map->elems)
	return ;
	ft_memcpy(map->elems, mapElems, 64 * sizeof(int));
	map->heigth = 8;
	map->width = 8;
	map_location.x = 200;
	map_location.y = 200;
	display_map(map, main_img, &map_location);
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
		free(mlx->mlx);
		free(mlx);
		return (NULL);
	}
	mlx->win = mlxwin;
	return (mlx);
}

void	testDrawLine(t_img *img)
{
	t_point *p1 = ft_calloc(1, sizeof(t_point));
	p1->x = 50;
	p1->y = 50;
	t_point *p2 = ft_calloc(1, sizeof(t_point));
	p2->x = 50;
	p2->y = 250;
	cub_drawLine(img, p1, p2);
}

int	main(int ac, char **av, char **env)
{

	if (!env)
		return (EXIT_FAILURE);


	t_mlx	*mlx;
	t_img	*main_img;

	(void) ac;
	(void) av;
	mlx = init_mlx();
	if (!mlx)
		return (EXIT_FAILURE);
	main_img = init_img(mlx, WIN_W, WIN_H);

	test_display_map(main_img);

	mlx_put_image_to_window(mlx->mlx, mlx->win, main_img->img, 0, 0);
	mlx_loop(mlx);
	mlx_destroy_window(mlx, mlx->win);
	mlx_destroy_display(mlx);
	free(mlx);
	free(main_img);
	return (EXIT_SUCCESS);
}
