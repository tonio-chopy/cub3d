#include "test.h"

t_walls	*cub_init_walls(t_data *data)
{
	t_walls	*walls;
	t_vec	*location;
	t_img	*img;

	location = cub_init_vec(0, 0);
	if (!location)
		cub_handle_fatal(data, "no location for walls\n");
	img = cub_init_img(data, WIN_W, WIN_H, location);
	if (!img)
	{
		free(location);
		cub_handle_fatal(data, "error creating img for walls\n");
	}
	walls = ft_calloc(1, sizeof(t_walls));
	if (!walls)
	{
		free(location);
		free(img);
		cub_handle_fatal(data, "error allocating mem for walls\n");
	}
	walls->img = img;
	walls->ceiling_ratio = 0.5;
	return (walls);
}

void	compute_offsets(t_data *data, t_minimap *minimap)
{
	double	mini_w;
	double	mini_h;

	mini_w = roundf(minimap->tilesize) * data->parsed_map->width;
	mini_h = roundf(minimap->tilesize) * data->parsed_map->heigth;
	if (mini_w < MINIMAP_SIZE)
		minimap->x_offset = (double)(MINIMAP_SIZE - mini_w) / 2.0f;
	if (mini_h < MINIMAP_SIZE)
		minimap->y_offset = (double)(MINIMAP_SIZE - mini_h) / 2.0f;
}

t_minimap	*cub_init_minimap(t_data *data)
{
	t_minimap	*minimap;
	t_vec		*minimap_location;
	t_img		*map;

	minimap_location = cub_init_vec(WIN_W - MINIMAP_SIZE - 10, \
WIN_H - MINIMAP_SIZE - 10);
	if (!minimap_location)
		cub_handle_fatal(data, MSG_ALLOC);
	map = cub_init_img(data, MINIMAP_SIZE, MINIMAP_SIZE, minimap_location);
	minimap = ft_calloc(1, sizeof(t_minimap));
	if (!minimap)
		free(map);
	if (!map || !minimap)
	{
		free(minimap_location);
		cub_handle_fatal(data, MSG_ALLOC);
	}
	minimap->map = map;
	if (data->parsed_map->heigth > data->parsed_map->width)
		minimap->tilesize = (double) MINIMAP_SIZE / \
(double) data->parsed_map->heigth;
	else
		minimap->tilesize = (double) MINIMAP_SIZE / \
(double) data->parsed_map->width;
	compute_offsets(data, minimap);
	return (minimap);
}

void	cub_init_graphics(t_data *data)
{
	data->minimap = cub_init_minimap(data);
	data->walls = cub_init_walls(data);
	data->tex = ft_calloc(4, sizeof(unsigned int *));
	if (!data->tex)
		cub_handle_fatal(data, MSG_ALLOC);
	data->tex[EAST] = cub_read_texture(data, data->parsed_map->ea_path);
	data->tex[WEST] = cub_read_texture(data, data->parsed_map->we_path);
	data->tex[NORTH] = cub_read_texture(data, data->parsed_map->no_path);
	data->tex[SOUTH] = cub_read_texture(data, data->parsed_map->so_path);
	cub_init_cam(data);
	cub_init_ray(data, data->cam->dir);
}
