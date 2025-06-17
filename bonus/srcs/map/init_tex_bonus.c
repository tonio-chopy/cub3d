/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tex_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:35:00 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/17 18:37:19 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static void	get_lr_tex(t_data *data)
{
	data->tex[RIGHT_CATCH] = cub_read_texture(data,
			"textures/keep_right_catch.xpm");
	data->tex[RIGHT_PASS_1] = cub_read_texture(data,
			"textures/passright1.xpm");
	data->tex[RIGHT_PASS_2] = cub_read_texture(data,
			"textures/passright2.xpm");
	data->tex[RIGHT_PASS_3] = cub_read_texture(data,
			"textures/passright3.xpm");
	data->tex[RIGHT_PASS_4] = cub_read_texture(data,
			"textures/passright4.xpm");
	data->tex[RIGHT_PASS_5] = cub_read_texture(data,
			"textures/passright5.xpm");
	data->tex[LEFT_PASS_1] = cub_read_texture(data,
			"textures/passleft1.xpm");
	data->tex[LEFT_PASS_2] = cub_read_texture(data,
			"textures/passleft2.xpm");
	data->tex[LEFT_PASS_3] = cub_read_texture(data,
			"textures/passleft3.xpm");
	data->tex[LEFT_PASS_4] = cub_read_texture(data,
			"textures/passleft4.xpm");
	data->tex[LEFT_PASS_5] = cub_read_texture(data,
			"textures/passleft5.xpm");
}

void	cub_get_goal_tex(t_data *data)
{
	data->tex[GOAL_LEFT] = cub_read_texture(data, "textures/goal01.xpm");
	data->tex[GOAL_CENTER] = cub_read_texture(data, "textures/goal02.xpm");
	data->tex[GOAL_RIGHT] = cub_read_texture(data, "textures/goal03.xpm");
	data->tex[CENTER_WAIT] = cub_read_texture(data, "textures/keep_face.xpm");
	data->tex[LEFT_FAIL] = cub_read_texture(data,
			"textures/keep_left_fail.xpm");
	data->tex[CENTER_FAIL] = cub_read_texture(data, "textures/keep_face.xpm");
	data->tex[RIGHT_FAIL] = cub_read_texture(data,
			"textures/keep_right_fail.xpm");
	data->tex[LEFT_CATCH] = cub_read_texture(data,
			"textures/keep_left_catch.xpm");
	data->tex[CENTER_CATCH] = cub_read_texture(data, "textures/keep_face.xpm");
	get_lr_tex(data);
	data->tex[EAST_HIT] = cub_read_texture(data,
			"textures/hiteast.xpm");
	data->tex[WEST_HIT] = cub_read_texture(data,
			"textures/hitwest.xpm");
	data->tex[TROPHY] = cub_read_texture(data,
			"textures/cupsquare.xpm");
}
