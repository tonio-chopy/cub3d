#include "test.h"

t_point	*get_coord_from_index(t_parsed_map *map, t_minimap *mini, int index)
{
	t_point	*p;
	float	x;
	float	y;

	x = (index % map->width) * mini->tilesize;
	y = (index / map->width) * mini->tilesize;
	p = init_pointf(x, y);
	// printf("coord for index %d are x%f and y%f\n", index, x, y);
	return (p);
}

void	draw_map_elem(t_data *data, t_img *img, int index, char value)
{
	int		color;
	t_point	*start;
	t_point *screenLocationStart;
	float	tilesize;

	screenLocationStart = data->minimap->map->location;
	tilesize = data->minimap->tilesize;
	if (value == ' ')
		color = MAP_OUT;
	else if (value == '1')
		color = MAP_WALL;
	else
		color = MAP_EMPTY;
	start = get_coord_from_index(data->parsed_map, data->minimap, index);
	if (data->debug)
		printf("drawing elem #%d (value %c) at x %d and y %d\n", index, value, start->x, start->y);
	cub_draw_rect(img, start, tilesize, tilesize, color);
	free(start);
}

void	cub_draw_minimap(t_data *data)
{
	int     i;
	int     nb_elems;
	char    map_value;

	map_value = ' ';
	if (data->parsed_map->heigth > data->parsed_map->width)
		data->minimap->tilesize = MINIMAP_SIZE / (float) data->parsed_map->heigth;
	else
		data->minimap->tilesize = MINIMAP_SIZE / (float) data->parsed_map->width;	
	i = 0;
	nb_elems = data->parsed_map->heigth * data->parsed_map->width;
	while (i < nb_elems)
	{
		map_value = data->parsed_map->elems[i];
		draw_map_elem(data, data->minimap->map, i, map_value);
		i++;
	}
}

void    cub_draw_player(t_data *data)
{
	t_point	norm_vector;

	if (!data->dir_vector)
	{
		data->player_pos = get_coord_from_index(data->parsed_map, data->minimap, data->parsed_map->player_pos);
		norm_vector.xf = 0.0f;
		norm_vector.yf = 0.0f;
		if (data->parsed_map->player_orientation == E_NORTH)
			norm_vector.yf = 1.0f;
		if (data->parsed_map->player_orientation == E_SOUTH)
			norm_vector.yf = -1.0f;
		if (data->parsed_map->player_orientation == E_EAST)
			norm_vector.xf = 1.0f;
		if (data->parsed_map->player_orientation == E_WEST)
			norm_vector.xf = -1.0f;
		data->dir_vector = &norm_vector;
	}
	cub_draw_cone(data->minimap->map, data->player_pos, data->dir_vector, 45, MINIMAP_SIZE / 2);
}