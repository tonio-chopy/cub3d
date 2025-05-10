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

t_parsed_map	*cub_init_map( void )
{
	t_parsed_map	*map;

	map = ft_calloc(1, sizeof(t_parsed_map));
	if (!map)
		return (NULL);
	char mapElems[] =
	{
		' ','1','1','1','1','1','1','1',\
		' ','1','0','0','0','0','0','1',\
		'1','1','0','1','0','0','0','1',\
		'1','0','0','1','0','S','0','1',\
		'1','0','1','1','0','0','0','1',\
		'1','1','1','1','0','0','0','1',\
		'1','1',' ','1','0','1','0','1',\
		'1','1',' ','1','1',' ','1','1',\
	};
	map->elems = ft_calloc(64, sizeof(int));
	if (!map->elems)
		return (NULL);
	ft_memcpy(map->elems, mapElems, (64) * sizeof(int));
	map->heigth = 8;
	map->width = 8;
	map->nb_elems = 64;
	map->player_orientation = 'W';
	map->player_pos = 29;
	return (map);
}

t_minimap	*init_minimap(t_data *data)
{
	t_minimap 	*minimap;
	t_point		*minimap_location;
	t_img		*map;

	minimap_location = init_point(WIN_W - MINIMAP_SIZE - 10, WIN_H - MINIMAP_SIZE - 10);
	if (!minimap_location)
		handle_fatal(data, NULL);
	map = cub_init_img(data, MINIMAP_SIZE, MINIMAP_SIZE, minimap_location);
	minimap = ft_calloc(1, sizeof(t_minimap));
	if (!map || !minimap)
		handle_fatal(data, NULL);
	minimap->map = map;
	minimap->player = NULL;
	return (minimap);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void) ac;
	(void) av;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	if (!env)
		return (EXIT_FAILURE);
	if (ac == 2)
		data->debug = av[1][0];
	else if (ac != 1)
		return (EXIT_FAILURE);
	data->parsed_map = cub_init_map();
	if (!data->parsed_map)
		return (EXIT_FAILURE);
	init_dir_vector(data);
	data->mlx = init_mlx();
	if (!data->mlx)
		return (EXIT_FAILURE);
	data->minimap = init_minimap(data);
	if (!data->minimap)
		return (EXIT_FAILURE);
	cub_draw_minimap(data);
	cub_draw_player(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->minimap->map->img, data->minimap->map->location->x, data->minimap->map->location->y);
	mlx_loop_hook(data->mlx->mlx, &cub_refresh, data);
	mlx_hook(data->mlx->win, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->mlx->win, KeyRelease, KeyReleaseMask, &handle_keyrelease, data->mlx);
	mlx_loop(data->mlx->mlx);
	clean_data(data);
	return (EXIT_SUCCESS);
}
