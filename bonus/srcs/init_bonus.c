/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:54:58 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/19 21:07:08 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static void	cub_init_sprite(t_data *data)
{
	t_sprite	*sprite;

	sprite = ft_calloc(1, sizeof(t_sprite));
	if (!sprite)
		cub_handle_fatal(data, MSG_ALLOC);
	data->sprite = sprite;
}

void	cub_init_bonus(t_data *data)
{
	system("paplay ./sound.wav &");
	data->parsed_map->opened_door_index = -1;
	cub_init_sprite(data);
	data->zbuffer = ft_calloc(WIN_W, sizeof(double));
	if (!data->zbuffer)
		cub_handle_fatal(data, MSG_ALLOC);
}

void	cub_init_hooks_bonus(t_data *data)
{	
	mlx_loop_hook(data->mlx->mlx, &cub_refresh_bonus, data);
	mlx_hook(data->mlx->win, MotionNotify, PointerMotionMask,
	&handle_mouse_rotate, (void *)data);
}