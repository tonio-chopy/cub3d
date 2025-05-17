#include "test.h"

t_vec	*cub_get_centercoord_norm(t_parsed_map *map, t_minimap *mini, int index)
{
	t_vec	*p;
	double	x;
	double	y;

	(void) mini;
	x = (index % map->width) + 0.5;
	y = (index / map->width) + 0.5;
	p = cub_init_vec_double(x, y);
	return (p);
}

t_vec	*cub_get_topleftcoord_adjusted(t_parsed_map *map, t_minimap *mini, int index)
{
	t_vec	*p;
	double	x;
	double	y;

	x = (index % map->width) * mini->tilesize;
	y = (index / map->width) * mini->tilesize;
	p = cub_init_vec_double(x, y);
	return (p);
}