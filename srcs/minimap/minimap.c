#include "test.h"

t_point	*cub_get_coord_from_index(t_parsed_map *map, t_minimap *mini, int index)
{
	t_point	*p;
	double	x;
	double	y;

	x = (index % map->width) * mini->tilesize;
	y = (index / map->width) * mini->tilesize;
	p = cub_init_point_double(x, y);
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
	start = cub_get_coord_from_index(data->parsed_map, data->minimap, index);
	if (data->debug == 'd')
		printf("drawing elem #%d (value %c) at x %d and y %d\n", index, value, start->x, start->y);
	cub_draw_rect(img, start, tilesize, tilesize, color);
	free(start);
}

void	cub_draw_minimap(t_data *data)
{
	int     i;
	char    map_value;

	map_value = ' ';
	
	i = 0;
	while (i < data->parsed_map->nb_elems)
	{
		map_value = data->parsed_map->elems[i];
		draw_map_elem(data, data->minimap->map, i, map_value);
		i++;
	}
}
void	cub_init_player_pos_and_cam(t_data *data)
{
	double	x_cam;

	data->player_pos = cub_get_coord_from_index(data->parsed_map, data->minimap, data->parsed_map->player_pos);
	x_cam = 2 * data->player_pos->xd / (double) MINIMAP_SIZE - 1; 
	data->cam_vector = cub_init_point_double(x_cam, 1.0);
}

void	cub_init_dir_vector(t_data *data)
{	
	t_point	*norm_vector;

	norm_vector = cub_init_point_double(0, 0);
	if (data->parsed_map->player_orientation == E_NORTH)
		norm_vector->yd = 1.0f;
	if (data->parsed_map->player_orientation == E_SOUTH)
		norm_vector->yd = -1.0f;
	if (data->parsed_map->player_orientation == E_EAST)
		norm_vector->xd = 1.0f;
	if (data->parsed_map->player_orientation == E_WEST)
		norm_vector->xd = -1.0f;
	data->dir_vector = norm_vector;
}

void    cub_draw_player(t_data *data)
{

	if (data->debug == 'v')
		printf("dir vector x = %f and y = %f\n", data->dir_vector->xd, data->dir_vector->yd);
	cub_draw_cone(data->minimap->map, data->player_pos, data->dir_vector, 60, MINIMAP_SIZE / 2);
}