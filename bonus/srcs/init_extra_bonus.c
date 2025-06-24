/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_extra_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 12:50:28 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/24 12:39:28 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_init_cup(t_data *data)
{
	t_sprite	*cup;

	cup = ft_calloc(1, sizeof(t_sprite));
	if (!cup)
		cub_handle_fatal(data, MSG_ALLOC);
	cup->sprites = ft_calloc(5, sizeof(t_sprite));
	if (!cup->sprites)
	{
		free(cup);
		cub_handle_fatal(data, MSG_ALLOC);
	}
	cup->sprites[0] = cub_read_texture(data, "textures/cup_0.xpm");
	cup->sprites[1] = cub_read_texture(data, "textures/cup_1.xpm");
	cup->sprites[2] = cub_read_texture(data, "textures/cup_2.xpm");
	cup->sprites[3] = cub_read_texture(data, "textures/cup_3.xpm");
	cup->sprite_nb = 4;
	data->cup = cup;
}

void	cub_init_ball(t_data *data)
{
	t_sprite	*ball;

	ball = ft_calloc(1, sizeof(t_sprite));
	if (!ball)
		cub_handle_fatal(data, MSG_ALLOC);
	ball->sprites = ft_calloc(5, sizeof(t_sprite));
	if (!ball->sprites)
	{
		free(ball);
		cub_handle_fatal(data, MSG_ALLOC);
	}
	ball->sprites[0] = cub_read_texture(data, "textures/balls_0.xpm");
	ball->sprites[1] = cub_read_texture(data, "textures/balls_1.xpm");
	ball->sprites[2] = cub_read_texture(data, "textures/balls_2.xpm");
	ball->sprites[3] = cub_read_texture(data, "textures/balls_3.xpm");
	ball->sprites[4] = cub_read_texture(data, "textures/balls_4.xpm");
	ball->sprite_nb = 5;
	data->ball = ball;
}
