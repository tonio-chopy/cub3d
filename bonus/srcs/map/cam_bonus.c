/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:35:01 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/28 17:11:09 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_update_plane_vector(t_data *data)
{
	t_vec	*vec;
	double	fov_rad;
	double	plane_len;

	fov_rad = ft_to_rad(FOV_DEGREES);
	plane_len = tan(fov_rad / 2.0);
	free(data->cam->plane);
	vec = cub_init_vec_double(-data->cam->dir->yd * plane_len,
			data->cam->dir->xd * plane_len);
	if (!vec)
		cub_handle_fatal(data, MSG_ALLOC);
	data->cam->plane = vec;
}

/*
 * as the origin is topleft, the vector will be positive for South and East
 */
void	cub_init_dir_vector(t_data *data)
{
	data->cam->dir = cub_init_vec_double(0, 0);
	if (!data->cam->dir)
		cub_handle_fatal(data, MSG_ALLOC);
	if (data->parsed_map->player_orientation == E_NORTH)
	{
		data->cam->dir->yd = -1.0f;
		data->cam->angle = 270;
	}
	if (data->parsed_map->player_orientation == E_SOUTH)
	{
		data->cam->dir->yd = 1.0f;
		data->cam->angle = 90;
	}
	if (data->parsed_map->player_orientation == E_EAST)
	{
		data->cam->dir->xd = 1.0f;
		data->cam->angle = 0;
	}
	if (data->parsed_map->player_orientation == E_WEST)
	{
		data->cam->dir->xd = -1.0f;
		data->cam->angle = 180;
	}
}

void	cub_init_cam(t_data *data)
{
	t_cam	*cam;

	cam = ft_calloc(1, sizeof(t_cam));
	if (!cam)
		cub_handle_fatal(data, "Error\n init cam");
	data->cam = cam;
	cub_init_dir_vector(data);
	cub_update_plane_vector(data);
	data->player_pos = cub_get_centercoord_norm(data->parsed_map, \
data->parsed_map->player_pos);
	if (!data->player_pos)
		cub_handle_fatal(data, MSG_ALLOC);
	data->cam->orig = data->player_pos;
}
