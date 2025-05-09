#include "test.h"

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

	printf("xstar is %d - w is %d - ystart s %d, h is %d\n", xstart, w, ystart, h);
	y = ystart;
	while (y < ystart + h)
	{
		x = xstart;
		while (x < xstart + w)
		{
			printf("x = %d, y = %d\n", x, y);
			cub_put_pix_to_img(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_map_elem(t_img *img, int index, int tile_type, t_point *screenLocationStart, int square_size, t_map *map)
{
	int	x;
	int	y;
	int	color;

	color = BLUE;
	if (tile_type == 1)
		color = GREEN;
	else if (tile_type == 2)
		color = RED;
	x = screenLocationStart->x + (index % map->width) * square_size;
	y = screenLocationStart->y + (index / map->width) * square_size;
	ft_put_green("drawing elem index ");
	printf("%d index at x %d and y %d\n", index, x, y);
	cub_draw_rect(img, x, y, square_size, square_size, color);
}

t_point	*init_point(int x, int y)
{
	t_point	*point;

	point = ft_calloc(1, sizeof(t_point));
	point->x = x;
	point->y = y;
	return (point);
}

void	display_map(t_map *map, t_img *img, t_point *screenLocation)
{
	int i;
	int map_elems;
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
	i = 0;
	map_elems = map->heigth * map->width;
	while (i < map_elems)
	{
		map_value = map->elems[i];
		draw_map_elem(img, i, map_value, screenLocation, square_size, map);
		i++;
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

t_map	*init_map( void )
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		return (NULL);
	int mapElems[] =
	{
		1,1,1,1,1,1,1,1,\
		1,0,0,0,0,0,0,1,\
		1,0,0,1,0,0,0,1,\
		1,0,0,1,0,0,0,1,\
		1,0,1,1,0,0,0,1,\
		1,0,0,0,0,2,0,1,\
		1,0,0,0,0,0,0,1,\
		1,1,1,1,1,1,1,1,\
	};
	map->elems = ft_calloc(64 + 1, sizeof(int));
	if (!map->elems)
		return (NULL);
	ft_memcpy(map->elems, mapElems, (64) * sizeof(int));
	map->heigth = 8;
	map->width = 8;
	map->location = init_point(WIN_W - MIN_W - 10, WIN_H - MIN_W - 10);
	return (map);
}

int refresh(void *param)
{
	t_data	*data;

	data = (t_data *) param;
	display_map(data->map, data->mini, data->map->location);
	return (EXIT_SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	t_mlx	*mlx;
	t_img	*minimap;
	t_data	*data;

	(void) ac;
	(void) av;
	if (!env)
		return (EXIT_FAILURE);
	mlx = NULL;
	init_mlx(mlx);
	if (!mlx)
		return (EXIT_FAILURE);
	minimap = init_img(mlx, WIN_W, WIN_H);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	data->map = init_map();
	data->mini = minimap;
	display_map(data->map, data->mini, data->map->location);

	mlx_put_image_to_window(mlx->mlx, mlx->win, minimap->img, 0, 0);
	mlx_loop_hook(mlx->mlx, &refresh, data);
	mlx_hook(mlx->win, KeyPress, KeyPressMask, &handle_keypress, mlx);
	mlx_hook(mlx->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, mlx);
	mlx_loop(mlx->mlx);
	free(data->map->location);
	free(data->map);
	clean_mlx_and_img(mlx, minimap);
	return (EXIT_SUCCESS);
}
