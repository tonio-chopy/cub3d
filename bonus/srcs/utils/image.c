/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:36:11 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/09 17:36:12 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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
    int	y = 35;
    int	color = 0xFFFFFF;

    mlx_string_put(data->mlx->mlx, data->mlx->win, 30, y, color, "=== Commandes cub3D ===");
    mlx_string_put(data->mlx->mlx, data->mlx->win, 30, (y += 25), color, "W/A/S/D : Deplacement");
    mlx_string_put(data->mlx->mlx, data->mlx->win, 30, (y += 25), color, "Fleche gauche/droite : Rotation");
    mlx_string_put(data->mlx->mlx, data->mlx->win, 30, (y += 25), color, "ESC : Quitter");
    mlx_string_put(data->mlx->mlx, data->mlx->win, 30, (y += 25), color, "H : Afficher/Masquer l'aide");
}
