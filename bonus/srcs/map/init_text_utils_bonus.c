/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_text_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 10:11:15 by alaualik          #+#    #+#             */
/*   Updated: 2025/07/05 10:12:09 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static void	get_right_pass_tex(t_data *data)
{
	data->tex[RIGHT_PASS_1] = cub_read_texture(data,
			"textures/passright1.xpm");
	if (!data->tex[RIGHT_PASS_1])
		cub_handle_fatal(data, "Error\n creating texture img");
	data->tex[RIGHT_PASS_2] = cub_read_texture(data,
			"textures/passright2.xpm");
	if (!data->tex[RIGHT_PASS_2])
		cub_handle_fatal(data, "Error\n creating texture img");
	data->tex[RIGHT_PASS_3] = cub_read_texture(data,
			"textures/passright3.xpm");
	if (!data->tex[RIGHT_PASS_3])
		cub_handle_fatal(data, "Error\n creating texture img");
	data->tex[RIGHT_PASS_4] = cub_read_texture(data,
			"textures/passright4.xpm");
	if (!data->tex[RIGHT_PASS_4])
		cub_handle_fatal(data, "Error\n creating texture img");
	data->tex[RIGHT_PASS_5] = cub_read_texture(data,
			"textures/passright5.xpm");
	if (!data->tex[RIGHT_PASS_5])
		cub_handle_fatal(data, "Error\n creating texture img");
}

static void	get_left_pass_tex(t_data *data)
{
	data->tex[LEFT_PASS_1] = cub_read_texture(data,
			"textures/passleft1.xpm");
	if (!data->tex[LEFT_PASS_1])
		cub_handle_fatal(data, "Error\n creating texture img");
	data->tex[LEFT_PASS_2] = cub_read_texture(data,
			"textures/passleft2.xpm");
	if (!data->tex[LEFT_PASS_2])
		cub_handle_fatal(data, "Error\n creating texture img");
	data->tex[LEFT_PASS_3] = cub_read_texture(data,
			"textures/passleft3.xpm");
	if (!data->tex[LEFT_PASS_3])
		cub_handle_fatal(data, "Error\n creating texture img");
	data->tex[LEFT_PASS_4] = cub_read_texture(data,
			"textures/passleft4.xpm");
	if (!data->tex[LEFT_PASS_4])
		cub_handle_fatal(data, "Error\n creating texture img");
	data->tex[LEFT_PASS_5] = cub_read_texture(data,
			"textures/passleft5.xpm");
	if (!data->tex[LEFT_PASS_5])
		cub_handle_fatal(data, "Error\n creating texture img");
}

void	get_lr_tex(t_data *data)
{
	data->tex[RIGHT_CATCH] = cub_read_texture(data,
			"textures/keep_right_catch.xpm");
	if (!data->tex[RIGHT_CATCH])
		cub_handle_fatal(data, "Error\n creating texture img");
	get_right_pass_tex(data);
	get_left_pass_tex(data);
}
