/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/01/27 11:23:00 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	cub_rgb_to_int(double r, double g, double b)
{
	unsigned int	color;

	color = 0;
	color |= (unsigned int)(b * 255);
	color |= (unsigned int)(g * 255) << 8;
	color |= (unsigned int)(r * 255) << 16;
	return (color);
}

int	cub_get_pix_color(t_img *img, int x, int y)
{
	char	*pixel;

	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (0);
	pixel = img->addr + (y * img->line_length + x * (img->bpp / 8));
	return (*(unsigned int *)(pixel));
}

void	cub_put_pix_to_img(t_img *img, double x, double y, unsigned int color)
{
	char	*pixel;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		pixel = img->addr + (int)(y * img->line_length + x * (img->bpp / 8));
		*(unsigned int *) pixel = color;
	}
}

void	cub_cpy_with_transparency(t_img *dest, t_img *from, int x_offset, \
int y_offset)
{
	int	x;
	int	y;
	int	x_dest;
	int	y_dest;
	int	color;

	y = 0;
	while (y < from->height)
	{
		x = 0;
		while (x < from->width)
		{
			color = cub_get_pix_color(from, x, y);
			if (color != INVISIBLE)
			{
				x_dest = x + x_offset;
				y_dest = y + y_offset;
				cub_put_pix_to_img(dest, x_dest, y_dest, color);
			}
			x++;
		}
		y++;
	}
}
