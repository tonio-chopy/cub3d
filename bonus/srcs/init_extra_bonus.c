/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_extra_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:50:28 by fpetit            #+#    #+#             */
/*   Updated: 2025/07/03 21:24:03 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static void	cub_load_cup_textures(t_data *data, t_sprite *cup)
{
	cup->sprites[0] = cub_read_texture(data, "textures/cup_0.xpm");
	if (!cup->sprites[0])
		cub_handle_fatal(data, "Error\n creating texture img");
	cup->sprites[1] = cub_read_texture(data, "textures/cup_1.xpm");
	if (!cup->sprites[1])
		cub_handle_fatal(data, "Error\n creating texture img");
	cup->sprites[2] = cub_read_texture(data, "textures/cup_2.xpm");
	if (!cup->sprites[2])
		cub_handle_fatal(data, "Error\n creating texture img");
	cup->sprites[3] = cub_read_texture(data, "textures/cup_3.xpm");
	if (!cup->sprites[3])
		cub_handle_fatal(data, "Error\n creating texture img");
}

static void	cub_init_cup_properties(t_sprite *cup)
{
	cup->sprite_nb = 4;
	cup->transform_y = 0;
	cup->transform_x = 0;
	cup->elem = E_CUP;
}

void	cub_init_cup(t_data *data)
{
	t_sprite	*cup;

	cup = ft_calloc(1, sizeof(t_sprite));
	if (!cup)
		cub_handle_fatal(data, MSG_ALLOC);
	cup->sprites = ft_calloc(4, sizeof(t_sprite));
	if (!cup->sprites)
	{
		free(cup);
		cub_handle_fatal(data, MSG_ALLOC);
	}
	data->cup = cup;
	cub_load_cup_textures(data, cup);
	cub_init_cup_properties(cup);
}

void	cub_init_balltextures(t_data *data)
{
	data->goal->ballsprites = ft_calloc(5, sizeof(t_sprite));
	if (!data->goal->ballsprites)
		cub_handle_fatal(data, MSG_ALLOC);
	data->goal->ballsprites[0] = cub_read_texture(data, "textures/balls_0.xpm");
	if (!data->goal->ballsprites[0])
		cub_handle_fatal(data, "Error\n creating texture img");
	data->goal->ballsprites[1] = cub_read_texture(data, "textures/balls_1.xpm");
	if (!data->goal->ballsprites[1])
		cub_handle_fatal(data, "Error\n creating texture img");
	data->goal->ballsprites[2] = cub_read_texture(data, "textures/balls_2.xpm");
	if (!data->goal->ballsprites[2])
		cub_handle_fatal(data, "Error\n creating texture img");
	data->goal->ballsprites[3] = cub_read_texture(data, "textures/balls_3.xpm");
	if (!data->goal->ballsprites[3])
		cub_handle_fatal(data, "Error\n creating texture img");
	data->goal->ballsprites[4] = cub_read_texture(data, "textures/balls_4.xpm");
	if (!data->goal->ballsprites[4])
		cub_handle_fatal(data, "Error\n creating texture img");
}
