/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:35:00 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/28 17:18:20 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static void	cub_get_goal_basic_tex(t_data *data)
{
	data->tex[GOAL_LEFT] = cub_read_texture(data, "textures/goal01.xpm");
	if (!data->tex[GOAL_LEFT])
		cub_handle_fatal(data, "Error\n creating texture img");
	data->tex[GOAL_CENTER] = cub_read_texture(data, "textures/goal02.xpm");
	if (!data->tex[GOAL_CENTER])
		cub_handle_fatal(data, "Error\n creating texture img");
	data->tex[GOAL_RIGHT] = cub_read_texture(data, "textures/goal03.xpm");
	if (!data->tex[GOAL_RIGHT])
		cub_handle_fatal(data, "Error\n creating texture img");
	data->tex[CENTER_WAIT] = cub_read_texture(data, "textures/keep_face.xpm");
	if (!data->tex[CENTER_WAIT])
		cub_handle_fatal(data, "Error\n creating texture img");
}

static void	cub_get_goal_fail_tex(t_data *data)
{
	data->tex[LEFT_FAIL] = cub_read_texture(data,
			"textures/keep_left_fail.xpm");
	if (!data->tex[LEFT_FAIL])
		cub_handle_fatal(data, "Error\n creating texture img");
	data->tex[CENTER_FAIL] = cub_read_texture(data, "textures/keep_face.xpm");
	if (!data->tex[CENTER_FAIL])
		cub_handle_fatal(data, "Error\n creating texture img");
	data->tex[RIGHT_FAIL] = cub_read_texture(data,
			"textures/keep_right_fail.xpm");
	if (!data->tex[RIGHT_FAIL])
		cub_handle_fatal(data, "Error\n creating texture img");
}

static void	cub_get_goal_catch_tex(t_data *data)
{
	data->tex[LEFT_CATCH] = cub_read_texture(data,
			"textures/keep_left_catch.xpm");
	if (!data->tex[LEFT_CATCH])
		cub_handle_fatal(data, "Error\n creating texture img");
	data->tex[CENTER_CATCH] = cub_read_texture(data, "textures/keep_face.xpm");
	if (!data->tex[CENTER_CATCH])
		cub_handle_fatal(data, "Error\n creating texture img");
}

static void	cub_get_goal_hit_tex(t_data *data)
{
	data->tex[EAST_HIT] = cub_read_texture(data,
			"textures/hiteast.xpm");
	if (!data->tex[EAST_HIT])
		cub_handle_fatal(data, "Error\n creating texture img");
	data->tex[WEST_HIT] = cub_read_texture(data,
			"textures/hitwest.xpm");
	if (!data->tex[WEST_HIT])
		cub_handle_fatal(data, "Error\n creating texture img");
	data->tex[TROPHY] = cub_read_texture(data,
			"textures/cupsquare.xpm");
	if (!data->tex[TROPHY])
		cub_handle_fatal(data, "Error\n creating texture img");
}

void	cub_get_goal_tex(t_data *data)
{
	cub_get_goal_basic_tex(data);
	cub_get_goal_fail_tex(data);
	cub_get_goal_catch_tex(data);
	get_lr_tex(data);
	cub_get_goal_hit_tex(data);
}
