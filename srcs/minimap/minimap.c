#include "test.h"

t_vec	*cub_get_centercoord_norm(t_parsed_map *map, t_minimap *mini, int index)
{
	t_vec	*p;
	double	x;
	double	y;

	(void) mini;
	x = (index % map->width) + 0.5;
	y = (index / map->width) + 0.5;
	p = cub_init_point_double(x, y);
	return (p);
}

t_vec	*cub_get_topleftcoord_adjusted(t_parsed_map *map, t_minimap *mini, int index)
{
	t_vec	*p;
	double	x;
	double	y;

	x = (index % map->width) * mini->tilesize;
	y = (index / map->width) * mini->tilesize;
	p = cub_init_point_double(x, y);
	return (p);
}

void	draw_map_elem(t_data *data, t_img *img, int index, char value)
{
	int		color;
	t_vec	*start;
	t_vec *screenLocationStart;
	float	tilesize;

	screenLocationStart = data->minimap->map->location;
	tilesize = data->minimap->tilesize;
	if (value == ' ')
		color = MAP_OUT;
	else if (value == '1')
		color = MAP_WALL;
	else
		color = MAP_EMPTY;
	start = cub_get_topleftcoord_adjusted(data->parsed_map, data->minimap, index);
	if (data->debug == 'd')
		printf("drawing elem #%d (value %c) at x %d and y %d\n", index, value, start->x, start->y);
	cub_draw_rect(img, start, tilesize - 0.1, tilesize - 0.1, color);
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

/*
 * make camera plane vector perpendicular to player direction
 */
void	cub_init_player_pos(t_data *data)
{
	data->player_pos = cub_get_centercoord_norm(data->parsed_map, data->minimap, data->parsed_map->player_pos);
}

// // TODO replace by a -90 rotate
// void	cub_update_cam_vector(t_data *data)
// {
// 	// t_point	*norm_vector;
// 	// double	x;
// 	// double	y;

// 	if (data->cam_vector)
// 		free(data->cam_vector);
// 	data->cam_vector = ft_rotate_vector_new(data->dir_vector, -90);
// 	// x = data->dir_vector->xd;
// 	// y = data->dir_vector->yd;
// 	// norm_vector = cub_init_point_double(FOV_SCALE * -y, FOV_SCALE * x);
// 	// data->cam_vector = norm_vector;
// }

void	cub_update_plane_vector(t_data *data)
{	
	// data->cam->plane_xd = 0;
	// data->cam->plane_yd = 0;
	// if (data->parsed_map->player_orientation == E_NORTH)
	// 	 = -1.0f * FOV_SCALE;
	// if (data->parsed_map->player_orientation == E_SOUTH)
	// 	 = 1.0f * FOV_SCALE;
	// if (data->parsed_map->player_orientation == E_EAST)
	// 	 = 1.0f * FOV_SCALE;
	// if (data->parsed_map->player_orientation == E_WEST)
	// 	 = -1.0f * FOV_SCALE;
	// data->cam_vector = norm_vector;
	t_vec	*vec;

	// vector.xd = data->cam->dir->xd;
	// vector.yd = data->cam->dir->yd;
	vec = ft_rotate_vector_new(data->cam->dir, -90);
	vec->xd *= FOV_SCALE;
	vec->yd *= FOV_SCALE;
	data->cam->plane = vec;
	// data->cam->plane_xd = vector.xd * FOV_SCALE;
	// data->cam->plane_yd = vector.yd * FOV_SCALE;
}

/*
 * as the origin is topleft, the vector will be positive for South and East
 */
void	cub_init_dir_vector(t_data *data)
{
	t_vec	*vec;

	vec = cub_init_point_double(0, 0);
	if (data->parsed_map->player_orientation == E_NORTH)
		vec->yd = -1.0f;
	if (data->parsed_map->player_orientation == E_SOUTH)
		vec->yd = 1.0f;
	if (data->parsed_map->player_orientation == E_EAST)
		vec->xd = 1.0f;
	if (data->parsed_map->player_orientation == E_WEST)
		vec->xd = -1.0f;
	data->cam->dir = vec;
}

void	cub_init_cam(t_data *data)
{
	t_cam	*cam;

	cam = ft_calloc(1, sizeof(t_cam));
	if (!cam)
		cub_handle_fatal(data, NULL);
	data->cam = cam;
	cub_init_dir_vector(data);
	cub_update_plane_vector(data);
	data->cam->orig = data->player_pos;
}

void    cub_draw_player(t_data *data)
{
	if (data->debug == 'v')
	{
		debug_data(data);
	}
	t_vec player;
	player.xd = data->player_pos->xd * data->minimap->tilesize;
	player.yd = data->player_pos->yd * data->minimap->tilesize;
	cub_draw_cone(data, data->minimap->map, &player, 60, 100);
}