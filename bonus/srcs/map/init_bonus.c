/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:35:08 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/24 12:42:12 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

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

static void	cub_init_minimap(t_data *data)
{
	t_vec		*minimap_location;
	t_img		*map;

	minimap_location = cub_init_vec(WIN_W - MINIMAP_SIZE - 10, WIN_H
			- MINIMAP_SIZE - 10);
	if (!minimap_location)
		cub_handle_fatal(data, MSG_ALLOC);
	map = cub_init_img(data, MINIMAP_SIZE, MINIMAP_SIZE, minimap_location);
	data->minimap = ft_calloc(1, sizeof(t_minimap));
	if (!data->minimap)
		free(map);
	if (!map || !data->minimap)
	{
		free(minimap_location);
		cub_handle_fatal(data, MSG_ALLOC);
	}
	data->minimap->map = map;
	if (data->parsed_map->heigth > data->parsed_map->width)
		data->minimap->tilesize = (double)MINIMAP_SIZE
			/ (double)data->parsed_map->heigth;
	else
		data->minimap->tilesize = (double)MINIMAP_SIZE
			/ (double)data->parsed_map->width;
	compute_offsets(data, data->minimap);
}

void	cub_init_goal(t_data *data)
{
	data->goal = ft_calloc(1, sizeof(t_goal));
	if (!data->goal)
		cub_handle_fatal(data, MSG_ALLOC);
	data->goal->position = GOAL_CENTER;
	data->goal->has_shot = false;
	data->goal->ended = false;
	data->goal->shootcount = 0;
	data->goal->win = false;
	data->goal->anim_count = 0;
	data->goal->ball_anim_count = 0;
	data->goal->current_song = -1;
	data->goal->songpid = -1;
	data->goal->effectpid = -1;
	data->goal->audio_process = NULL;
	data->goal->effect_process = NULL;
	data->goal->can_shoot = false;
	data->goal->can_see_ball = false;
	data->goal->can_see_goal = false;
	data->goal->ok = cub_init_img_from_xpm(data, 100, 100, "textures/ok.xpm");
	data->goal->ko = cub_init_img_from_xpm(data, 100, 100, "textures/ko.xpm");
	data->goal->songs[ENSEMBLE] = "ensemble.wav";
	data->goal->songs[KIKI] = "kmb.wav";
	data->goal->songs[ROJA] = "roja.wav";
	data->goal->songs[KICK] = "kick.wav";
	data->goal->songs[BOO] = "boo.wav";
	data->goal->songs[GOAL] = "goal.wav";
}

void	cub_init_graphics(t_data *data)
{
	cub_init_minimap(data);
	data->walls = cub_init_walls(data);
	data->tex = ft_calloc(28, sizeof(unsigned int *));
	if (!data->tex)
		cub_handle_fatal(data, MSG_ALLOC);
	data->tex[NORTH] = cub_read_texture(data, data->parsed_map->paths[NORTH]);
	data->tex[SOUTH] = cub_read_texture(data, data->parsed_map->paths[SOUTH]);
	data->tex[WEST] = cub_read_texture(data, data->parsed_map->paths[WEST]);
	data->tex[EAST] = cub_read_texture(data, data->parsed_map->paths[EAST]);
	cub_get_goal_tex(data);
	cub_init_ball(data);
	cub_init_cup(data);
	cub_init_cam(data);
	cub_init_ray(data, data->cam->dir);
	cub_init_goal(data);
	cub_play_song(data, ENSEMBLE);
}
