/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/29 14:32:39 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_walls	*cub_init_walls(t_data *data)
{
	t_walls	*walls;
	t_vec	*location;
	t_img	*img;

	location = cub_init_vec(0, 0);
	if (!location)
		cub_handle_fatal(data, "no location for walls");
	img = cub_init_img(data, WIN_W, WIN_H, location);
	if (!img)
	{
		free(location);
		cub_handle_fatal(data, "Error\n creating img for walls");
	}
	walls = ft_calloc(1, sizeof(t_walls));
	if (!walls)
	{
		cub_clean_img(data, img);
		cub_handle_fatal(data, "Error\n allocating mem for walls");
	}
	walls->img = img;
	walls->ceiling_ratio = 0.5;
	return (walls);
}

void	cub_init_graphics(t_data *data)
{
	data->walls = cub_init_walls(data);
	data->text_nb = 4;
	data->tex = ft_calloc(data->text_nb, sizeof(unsigned int *));
	if (!data->tex)
		cub_handle_fatal(data, MSG_ALLOC);
	data->tex[NORTH] = cub_read_texture(data, data->parsed_map->paths[NORTH]);
	data->tex[SOUTH] = cub_read_texture(data, data->parsed_map->paths[SOUTH]);
	data->tex[WEST] = cub_read_texture(data, data->parsed_map->paths[WEST]);
	data->tex[EAST] = cub_read_texture(data, data->parsed_map->paths[EAST]);
	if (!data->tex[EAST] || !data->tex[WEST] || !data->tex[SOUTH] \
|| !data->tex[NORTH])
		cub_handle_fatal(data, MSG_TEX);
	cub_init_cam(data);
	cub_init_ray(data, data->cam->dir);
}
