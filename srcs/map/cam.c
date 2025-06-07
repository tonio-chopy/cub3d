#include "test.h"

void	cub_update_plane_vector(t_data *data)
{
	t_vec	*vec;

	vec = ft_rotate_vector_new(data->cam->dir, -90);
	vec->xd *= FOV_SCALE;
	vec->yd *= FOV_SCALE;
	data->cam->plane = vec;
}

/*
 * as the origin is topleft, the vector will be positive for South and East
 */
void	cub_init_dir_vector(t_data *data)
{
	t_vec	*vec;

	vec = cub_init_vec_double(0, 0);
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

t_vec	*cub_get_player_position(t_parsed_map *map)
{
	int		x;
	int		y;
	t_vec	*pos;

	x = map->player_pos % map->width;
	y = map->player_pos / map->width;
	pos = cub_init_vec_double((double)x + 0.5, (double)y + 0.5);
	return (pos);
}

void	cub_init_cam(t_data *data)
{
	t_cam	*cam;

	cam = ft_calloc(1, sizeof(t_cam));
	if (!cam)
		cub_handle_fatal(data, "error init cam\n");
	data->cam = cam;
	cub_init_dir_vector(data);
	cub_update_plane_vector(data);
	data->player_pos = cub_get_player_position(data->parsed_map);
	data->cam->orig = data->player_pos;
}
