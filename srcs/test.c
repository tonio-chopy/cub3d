#include "test.h"

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

t_map	*cub_init_map( void )
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
	return (map);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	t_point	*minimap_location;

	(void) ac;
	(void) av;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	if (!env)
		return (EXIT_FAILURE);
	if (ac == 2 && av[1][0] == 'd')
		data->debug = true;
	else if (ac != 1)
		return (EXIT_FAILURE);
	data->map = cub_init_map();
	data->mlx = init_mlx();
	minimap_location = init_point(WIN_W - MINIMAP_SIZE - 10, WIN_H - MINIMAP_SIZE - 10);
	data->mini = cub_init_img(data->mlx, WIN_W, WIN_H, minimap_location);
	if (!data->mlx || !data->map || !data->mini)
		return (EXIT_FAILURE);
	cub_display_map(data->map, data->mini, data->mini->location);

	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->mini->img, 0, 0);
	mlx_loop_hook(data->mlx->mlx, &cub_refresh, data);
	mlx_hook(data->mlx->win, KeyPress, KeyPressMask, &handle_keypress, data->mlx);
	mlx_hook(data->mlx->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, data->mlx);
	mlx_loop(data->mlx->mlx);
	free(data->mini->location);
	free(data->map);
	clean_mlx_and_img(data->mlx, data->mini);
	free(data);
	return (EXIT_SUCCESS);
}
