/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:35:01 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/17 16:56:53 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

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
	{
		data->cam->angleNorthDeg = 0;
		vec->yd = -1.0f;
	}
	if (data->parsed_map->player_orientation == E_SOUTH)
	{
		data->cam->angleNorthDeg = 180;
		vec->yd = 1.0f;
	}
	if (data->parsed_map->player_orientation == E_EAST)
	{
		data->cam->angleNorthDeg = 90;
		vec->xd = 1.0f;
	}
	if (data->parsed_map->player_orientation == E_WEST)
	{
		data->cam->angleNorthDeg = 270;
		vec->xd = -1.0f;
	}
	data->cam->dir = vec;
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
	data->player_pos = cub_get_centercoord_norm(data->parsed_map, \
data->parsed_map->player_pos);
	data->cam->orig = data->player_pos;
}
