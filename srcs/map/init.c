/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/01/27 11:23:00 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

t_walls	*cub_init_walls(t_data *data)
{
	t_walls	*walls;
	t_vec	*location;
	t_img	*img;

	location = cub_init_vec(0, 0);
	if (!location)
		cub_handle_fatal(data, "no location for walls\n");
	img = cub_init_img(data, WIN_W, WIN_H, location);
	if (!img)
	{
		free(location);
		cub_handle_fatal(data, "error creating img for walls\n");
	}
	walls = ft_calloc(1, sizeof(t_walls));
	if (!walls)
	{
		free(location);
		free(img);
		cub_handle_fatal(data, "error allocating mem for walls\n");
	}
	walls->img = img;
	walls->ceiling_ratio = 0.5;
	return (walls);
}

void	cub_init_graphics(t_data *data)
{
	data->walls = cub_init_walls(data);
	data->tex = ft_calloc(4, sizeof(unsigned int *));
	if (!data->tex)
		cub_handle_fatal(data, MSG_ALLOC);
	data->tex[NORTH] = cub_read_texture(data, data->parsed_map->paths[NORTH]);
	data->tex[SOUTH] = cub_read_texture(data, data->parsed_map->paths[SOUTH]);
	data->tex[WEST] = cub_read_texture(data, data->parsed_map->paths[WEST]);
	data->tex[EAST] = cub_read_texture(data, data->parsed_map->paths[EAST]);
	cub_init_cam(data);
	cub_init_ray(data, data->cam->dir);
}
