#include "test.h"

static void	draw_map_elem(t_img *img, int index, int tile_type, t_point *screenLocationStart, int square_size, t_map *map)
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
	cub_draw_rect(img, x, y, square_size, square_size, color);
}

void	cub_display_map(t_map *map, t_img *img, t_point *screenLocation)
{
	int i;
	int map_elems;
	int	map_value;
	int	square_size;

	if (map->heigth > map->width)
	{
		square_size = MINIMAP_SIZE / map->heigth;
	}
	else
	{
		square_size = MINIMAP_SIZE / map->width;
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