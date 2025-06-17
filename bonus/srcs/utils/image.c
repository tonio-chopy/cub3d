/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:36:11 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/17 20:50:47 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_update_img_info(t_img *img, int bpp, int line_length, int endian)
{
	img->bpp = bpp;
	img->line_length = line_length;
	img->endian = endian;
}

void	cub_update_img_coord(t_img *img, int width, int height, t_vec *location)
{
	img->width = width;
	img->height = height;
	if (location)
		img->location = location;
}

void	cub_draw_help(t_data *data)
{
	int	y;
	int	color;

	y = 35;
	color = 0xFFFFFF;
	mlx_string_put(data->mlx->mlx, data->mlx->win, 30, y, color,
		"=== cub3D commands ===");
	mlx_string_put(data->mlx->mlx, data->mlx->win, 30, (y += 25), color,
		"W/A/S/D : Movement");
	mlx_string_put(data->mlx->mlx, data->mlx->win, 30, (y += 25), color,
		"⬅️ ➡️: Rotation");
	mlx_string_put(data->mlx->mlx, data->mlx->win, 30, (y += 25), color,
		"ESC : Quit");
	mlx_string_put(data->mlx->mlx, data->mlx->win, 30, (y += 25), color,
		"H : Toggle display for help");
}

void	cub_clear_img(t_img *img)
{
	double	y;
	double	x;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			cub_put_pix_to_img(img, x, y, INVISIBLE);
			x++;
		}
		y++;
	}
}
