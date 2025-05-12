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

// ne pas oublier de remplacer le NSWE par un 0 dans le parsing
t_parsed_map	*cub_init_map( void )
{
	t_parsed_map	*map;

	map = ft_calloc(1, sizeof(t_parsed_map));
	if (!map)
		return (NULL);
	char mapElems[] =
	{
		'1','1','1','1','1','1','1','1',\
		'1','0','0','0','0','0','0','1',\
		'1','0','1','0','0','1','0','1',\
		'1','0','0','0','0','0','0','1',\
		'1','0','1','0','0','1','0','1',\
		'1','0','0','1','1','0','0','1',\
		'1','0','0','0','0','0','0','1',\
		'1','1','1','1','1','1','1','1',\
	};
	map->elems = ft_calloc(64, sizeof(int));
	if (!map->elems)
		return (NULL);
	ft_memcpy(map->elems, mapElems, (64) * sizeof(int));
	map->heigth = 8;
	map->width = 8;
	map->nb_elems = 64;
	map->player_orientation = 'N';
	map->player_pos = 50;
	return (map);
}

t_minimap	*init_minimap(t_data *data)
{
	t_minimap 	*minimap;
	t_point		*minimap_location;
	t_img		*map;

	minimap_location = cub_init_point(WIN_W - MINIMAP_SIZE - 10, WIN_H - MINIMAP_SIZE - 10);
	if (!minimap_location)
		cub_handle_fatal(data, NULL);
	map = cub_init_img(data, MINIMAP_SIZE, MINIMAP_SIZE, minimap_location);
	minimap = ft_calloc(1, sizeof(t_minimap));
	if (!map || !minimap)
		cub_handle_fatal(data, NULL);
	minimap->map = map;
	minimap->player = NULL;
	if (data->parsed_map->heigth > data->parsed_map->width)
		minimap->tilesize = MINIMAP_SIZE / (float) data->parsed_map->heigth;
	else
		minimap->tilesize = MINIMAP_SIZE / (float) data->parsed_map->width;
	return (minimap);
}

void	debug_ray(t_ray *ray)
{
	printf("\n\n====RAY\n");
	if (ray->current_cell)
	{
		ft_put_pink("current cell: ");
		printf("x %d y %d\n", ray->current_cell->x, ray->current_cell->y);
	}
	if (ray->step_cell)
	{
		ft_put_pink("step cell: ");
		printf("x %d y %d\n", ray->step_cell->x, ray->step_cell->y);
	}
	if (ray->raydir)
	{
		ft_put_pink("ray dir: ");
		printf("x %f y %f\n", ray->raydir->xd, ray->raydir->yd);
	}
	if (ray->delta)
	{
		ft_put_pink("delta: ");
		printf("x %f y %f\n", ray->delta->xd, ray->delta->yd);
	}
	if (ray->side_dist)
	{
		ft_put_pink("side dist: ");
		printf("x %f y %f\n", ray->side_dist->xd, ray->side_dist->yd);
	}
}

void	debug_data(t_data *data)
{
	ft_put_pink("dir\n");
	printf("x %f\ny %f\n", data->dir_vector->xd, data->dir_vector->yd);
	ft_put_pink("pos\n");
	printf("x %f\ny %f\n", data->player_pos->xd, data->player_pos->yd);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	(void) ac;
	(void) av;
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (EXIT_FAILURE);
	data->rotates_left = false;
	data->rotates_right = false;
	data->move_forward = false;
	data->move_backward = false;
	data->move_left = false;
	data->move_right = false;
	if (!env)
		return (EXIT_FAILURE);
	if (ac == 2)
		data->debug = av[1][0];
	else if (ac != 1)
		return (EXIT_FAILURE);
	data->mlx = cub_init_mlx();
	if (!data->mlx)
		return (EXIT_FAILURE);
	data->parsed_map = cub_init_map();
	if (!data->parsed_map)
		return (EXIT_FAILURE);
	data->minimap = init_minimap(data);
	if (!data->minimap)
		return (EXIT_FAILURE);
	cub_init_dir_vector(data);
	cub_init_cam_vector(data);
	cub_init_player_pos(data);
	cub_draw_minimap(data);
	cub_draw_player(data);
	ft_printfd(1, "before loop hook\n");
	mlx_loop_hook(data->mlx->mlx, &cub_refresh, data);
	ft_printfd(1, "before keypress hook\n");
	mlx_hook(data->mlx->win, KeyPress, KeyPressMask, &cub_handle_keypress, data);
	ft_printfd(1, "before keyrelease hook\n");
	mlx_hook(data->mlx->win, KeyRelease, KeyReleaseMask, &cub_handle_keyrelease, data);
	ft_printfd(1, "before loop\n");
	mlx_loop(data->mlx->mlx);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->minimap->map->img, data->minimap->map->location->x, data->minimap->map->location->y);
	cub_clean_data(data);
	return (EXIT_SUCCESS);
}
