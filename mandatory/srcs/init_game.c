/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/15 14:37:36 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static void	setup_mlx_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx->mlx, &cub_refresh, data);
	mlx_hook(data->mlx->win, KeyPress, KeyPressMask, &cub_handle_keypress,
		data);
	mlx_hook(data->mlx->win, KeyRelease, KeyReleaseMask, &cub_handle_keyrelease,
		data);
	mlx_hook(data->mlx->win, DestroyNotify, NoEventMask, &handle_click_on_close,
		(void *)data);
}

void	init_and_start_game(t_data *data)
{
	system("paplay ./sound.wav &");
	cub_init_graphics(data);
	cub_draw_ceiling_and_floor(data);
	cub_draw_walls(data);
	setup_mlx_hooks(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->walls->img->img, 0, 0);
	mlx_loop(data->mlx->mlx);
}
