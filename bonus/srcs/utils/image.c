/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:36:11 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/19 19:26:02 by fpetit           ###   ########.fr       */
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
