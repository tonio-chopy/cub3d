/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:36:05 by alaualik          #+#    #+#             */
/*   Updated: 2025/07/03 19:50:33 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	cub_rgb_to_int(double r, double g, double b)
{
	unsigned int	color;

	color = 0;
	color |= (unsigned int)(b * 255);
	color |= (unsigned int)(g * 255) << 8;
	color |= (unsigned int)(r * 255) << 16;
	return (color);
}

unsigned int	get_sprite_pixel_color(t_data *data, t_sprite *sprite, \
int tex_x, int tex_y)
{
	int	anim_index;
	int	index;

	if (tex_x < 0 || tex_x >= CUP_SIZE || tex_y < 0 || tex_y >= CUP_SIZE)
		return (INVISIBLE);
	if (sprite->elem == E_CUP)
	{
		anim_index = data->goal->cup_anim_count / 10;
		index = tex_y * CUP_SIZE + tex_x;
		return (data->cup->sprites[anim_index][index]);
	}
	else
	{
		anim_index = data->goal->ball_anim_count / 10;
		index = tex_y * BALL_SIZE + tex_x;
		return (data->goal->ballsprites[anim_index][index]);
	}
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
