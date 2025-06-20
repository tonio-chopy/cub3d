/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:15:22 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/20 15:44:29 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static void	cub_draw_help_background(t_data *data)
{
	int	x;
	int	y;

	y = HELP_Y;
	while (y < HELP_Y + HELP_H)
	{
		x = HELP_X;
		while (x < HELP_X + HELP_W)
		{
			cub_put_pix_to_img(data->walls->img, x, y, HELP_COL);
			x++;
		}
		y++;
	}
}

void	cub_draw_help(t_data *data)
{
	int	y;

	cub_draw_help_background(data);
	y = HELP_Y + 5;
	mlx_string_put(data->mlx->mlx, data->mlx->win, HELP_X + 5, y, HELP_TEXT,
		"=== cub3D commands ===");
	mlx_string_put(data->mlx->mlx, data->mlx->win, HELP_X + 5, (y += 25), \
HELP_TEXT,
		"W/A/S/D : Movement");
	mlx_string_put(data->mlx->mlx, data->mlx->win, HELP_X + 5, (y += 25), \
HELP_TEXT,
		"⬅️ ➡️: Rotation");
	mlx_string_put(data->mlx->mlx, data->mlx->win, HELP_X + 5, (y += 25), \
HELP_TEXT,
		"ESC : Quit");
	mlx_string_put(data->mlx->mlx, data->mlx->win, HELP_X + 5, (y += 25), \
HELP_TEXT,
		"H : Toggle display for help");
}