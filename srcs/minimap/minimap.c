#include "test.h"

static void	draw_map_elem(t_img *img, int index, char value, t_point *screenLocationStart, int square_size, t_map *map)
{
	int	x;
	int	y;
	int	color;

	color = MAP_EMPTY;
	if (value == '1')
		color = MAP_WALL;
	x = screenLocationStart->x + (index % map->width) * square_size;
	y = screenLocationStart->y + (index / map->width) * square_size;
	cub_draw_rect(img, x, y, square_size, square_size, color);
}

void	cub_display_map(t_map *map, t_img *img, t_point *screenLocation)
{
	int     i;
	int     nb_elems;
	char    map_value;
	int     square_size;

	if (map->heigth > map->width)
	{
		square_size = MINIMAP_SIZE / map->heigth;
	}
	else
	{
		square_size = MINIMAP_SIZE / map->width;
	}
	i = 0;
	nb_elems = map->heigth * map->width;
	while (i < nb_elems)
	{
		map_value = map->elems[i];
        if (map_value == E_WEST || map_value == E_EAST || map_value == E_NORTH || map_value == E_SOUTH)
			map->player_pos = i;
		draw_map_elem(img, i, map_value, screenLocation, square_size, map);
		i++;
	}
}

void    cub_move_player_minimap(t_data *data, t_dir dir)
{

}