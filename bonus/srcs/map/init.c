/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:35:08 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/09 17:35:09 by alaualik         ###   ########.fr       */
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

void	compute_offsets(t_data *data, t_minimap *minimap)
{
	double	mini_w;
	double	mini_h;

	mini_w = roundf(minimap->tilesize) * data->parsed_map->width;
	mini_h = roundf(minimap->tilesize) * data->parsed_map->heigth;
	if (mini_w < MINIMAP_SIZE)
		minimap->x_offset = (double)(MINIMAP_SIZE - mini_w) / 2.0f;
	if (mini_h < MINIMAP_SIZE)
		minimap->y_offset = (double)(MINIMAP_SIZE - mini_h) / 2.0f;
}

t_minimap	*cub_init_minimap(t_data *data)
{
	t_minimap	*minimap;
	t_vec		*minimap_location;
	t_img		*map;

	minimap_location = cub_init_vec(WIN_W - MINIMAP_SIZE - 10, \
WIN_H - MINIMAP_SIZE - 10);
	if (!minimap_location)
		cub_handle_fatal(data, MSG_ALLOC);
	map = cub_init_img(data, MINIMAP_SIZE, MINIMAP_SIZE, minimap_location);
	minimap = ft_calloc(1, sizeof(t_minimap));
	if (!minimap)
		free(map);
	if (!map || !minimap)
	{
		free(minimap_location);
		cub_handle_fatal(data, MSG_ALLOC);
	}
	minimap->map = map;
	if (data->parsed_map->heigth > data->parsed_map->width)
		minimap->tilesize = (double) MINIMAP_SIZE / \
(double) data->parsed_map->heigth;
	else
		minimap->tilesize = (double) MINIMAP_SIZE / \
(double) data->parsed_map->width;
	compute_offsets(data, minimap);
	return (minimap);
}

void	cub_init_goal(t_data *data)
{
	data->goal = ft_calloc(1, sizeof(t_goal));
	if (!data->goal)
		cub_handle_fatal(data, MSG_ALLOC);
	data->goal->imgs = ft_calloc(7, sizeof(t_img));
	if (!data->goal->imgs)
		cub_handle_fatal(data, MSG_ALLOC);
	data->goal->position = GOAL_CENTER;
	data->goal->has_catched = false;
	data->goal->win = false;
}

void	cub_init_graphics(t_data *data)
{
	// int i;

	data->minimap = cub_init_minimap(data);
	data->walls = cub_init_walls(data);
	
	data->tex = ft_calloc(14, sizeof(unsigned int *));
	if (!data->tex)
		cub_handle_fatal(data, MSG_ALLOC);
	data->tex[NORTH] = cub_read_texture(data, data->parsed_map->paths[NORTH]);
	data->tex[SOUTH] = cub_read_texture(data, data->parsed_map->paths[SOUTH]);
	data->tex[WEST] = cub_read_texture(data, data->parsed_map->paths[WEST]);
	data->tex[EAST] = cub_read_texture(data, data->parsed_map->paths[EAST]);
	data->tex[GOAL_LEFT] = cub_read_texture(data, "textures/goal01.xpm");
	data->tex[GOAL_CENTER] = cub_read_texture(data, "textures/goal02.xpm");
	data->tex[GOAL_RIGHT] = cub_read_texture(data, "textures/goal03.xpm");
	data->tex[CENTER_WAIT] = cub_read_texture(data, "textures/keep_face.xpm");
	data->tex[LEFT_FAIL] = cub_read_texture(data, "textures/keep_left_fail.xpm");
	data->tex[CENTER_FAIL] = cub_read_texture(data, "textures/keep_face.xpm");
	data->tex[RIGHT_FAIL] = cub_read_texture(data, "textures/keep_right_fail.xpm");
	data->tex[LEFT_CATCH] = cub_read_texture(data, "textures/keep_left_catch.xpm");
	data->tex[CENTER_CATCH] = cub_read_texture(data, "textures/keep_face.xpm");
	data->tex[RIGHT_CATCH] = cub_read_texture(data, "textures/keep_right_catch.xpm");
	// i = 0;
	// while (i < 14)
	// {
	// 	if(!data->tex[i])
	// 		cub_handle_fatal(data, MSG_ALLOC);
	// 	i++;
	// }
	cub_init_cam(data);
	cub_init_ray(data, data->cam->dir);
	cub_init_goal(data);
}
