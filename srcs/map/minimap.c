#include "test.h"

void	draw_map_elem(t_data *data, t_img *img, int index, char value)
{
	int		color;
	t_vec	*start;
	double	tilesize;
	t_shape	rect;

	tilesize = data->minimap->tilesize;
	if (value == ' ')
		color = INVISIBLE;
	else if (value == '1')
		color = MAP_WALL;
	else
		color = MAP_EMPTY;
	start = cub_get_topleftcoord_adjusted(data->parsed_map, data->minimap, \
index);
	if (data->debug == 'd')
		printf("drawing elem #%d (value %c) at x %d and y %d\n", index, value, \
start->x, start->y);
	init_shape(start, roundf(tilesize) - 1, RECTANGLE, &rect);
	rect.color = color;
	rect.heigth = roundf(tilesize) - 1;
	cub_draw_rect(img, &rect);
	free(start);
}

void	cub_draw_minimap(t_data *data)
{
	int		i;
	char	map_value;

	map_value = ' ';
	i = 0;
	while (i < data->parsed_map->nb_elems)
	{
		map_value = data->parsed_map->elems[i];
		draw_map_elem(data, data->minimap->map, i, map_value);
		i++;
	}
}

void	cub_draw_player(t_data *data)
{
	t_vec	player;

	if (data->debug == 'v')
		debug_data(data);
	player.xd = data->minimap->x_offset + data->player_pos->xd * \
data->minimap->tilesize;
	player.yd = data->minimap->y_offset + data->player_pos->yd * \
data->minimap->tilesize;
	cub_draw_fov(data, &player, 60, 100);
}
