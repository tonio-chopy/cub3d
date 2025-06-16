/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/01/27 11:23:00 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <math.h>

void	cub_put_pix_to_img_inv(t_img *img, double x, double y, \
unsigned int color)
{
	char	*pixel;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		pixel = img->addr + (int)(y * img->line_length + x * (img->bpp / 8));
		if (color != INVISIBLE)
			*(unsigned int *) pixel = color;
	}
}

void	cub_drawline(t_img *img, t_vec *from, t_vec *to, int color)
{
	int		steps;
	t_vec	delta;
	t_vec	inc;
	t_vec	draw;
	int		i;

	delta.xd = to->xd - from->xd;
	delta.yd = to->yd - from->yd;
	if (fabs(delta.xd) > fabs(delta.yd))
		steps = round(fabs(delta.xd));
	else
		steps = round(fabs(delta.yd));
	inc.xd = delta.xd / (double) steps;
	inc.yd = delta.yd / (double) steps;
	draw.xd = from->xd;
	draw.yd = from->yd;
	i = 0;
	while (i < steps)
	{
		cub_put_pix_to_img(img, roundf(draw.xd), roundf(draw.yd), color);
		draw.xd += inc.xd;
		draw.yd += inc.yd;
		i++;
	}
}

/* 
 * starting from topleft corner
 */
void	cub_draw_rect(t_img *img, t_shape *rect)
{
	double	x;
	double	y;

	y = rect->start->yd;
	while (y < rect->start->yd + rect->heigth)
	{
		x = rect->start->xd;
		while ((double) x < rect->start->xd + rect->width)
		{
			cub_put_pix_to_img_inv(img, roundf(x), roundf(y), rect->color);
			x++;
		}
		y++;
	}
}

void	init_shape(t_vec *start, double width, t_shapetype type, t_shape *shape)
{
	shape->type = type;
	shape->start = start;
	shape->width = width;
}

static int	cub_get_flag_wave(int y, double wave_offset)
{
	int	wave_table[20] = {0, 1, 2, 2, 1, 0, -1, -2, -2, -1, 0, 1, 2, 2, 1, 0, -1, -2, -2, -1};
	int	index;
	
	index = ((int)(y + wave_offset * 3)) % 20;
	return (wave_table[index]);
}

static unsigned int	cub_get_flag_color(int stripe)
{
	if (stripe == 0)
		return (0x002395ED);
	else if (stripe == 1)
		return (0x00FFFFFF);
	else
		return (0x00ED2939);
}

static void	cub_draw_flag_stripe(t_data *data, int start_x, int start_y, 
	int stripe)
{
	int				x;
	int				y;
	int				wave_x;
	unsigned int	color;

	color = cub_get_flag_color(stripe);
	y = 0;
	while (y < 50)
	{
		wave_x = cub_get_flag_wave(y, data->flag_wave_offset);
		x = 0;
		while (x < 30)
		{
			cub_put_pix_to_img(data->walls->img, 
				start_x + stripe * 30 + x + wave_x, 
				start_y + y, color);
			x++;
		}
		y++;
	}
}

static void	cub_draw_flag_pole(t_data *data, int start_x, int start_y)
{
	int	x;
	int	y;

	x = -6;
	while (x < -2)
	{
		y = -5;
		while (y < 65)
		{
			cub_put_pix_to_img(data->walls->img, start_x + x, start_y + y, 
				cub_rgb_to_int(101, 67, 33));
			y++;
		}
		x++;
	}
}

void	cub_draw_french_flag(t_data *data)
{
	int	start_x;
	int	start_y;

	data->flag_frame++;
	if (data->flag_frame >= 8)
	{
		data->flag_frame = 0;
		data->flag_wave_offset += 0.2;
		if (data->flag_wave_offset > 6.28)
			data->flag_wave_offset = 0.0;
	}
	start_x = WIN_W - 100;
	start_y = 20;
	cub_draw_flag_pole(data, start_x, start_y);
	cub_draw_flag_stripe(data, start_x, start_y, 0);
	cub_draw_flag_stripe(data, start_x, start_y, 1);
	cub_draw_flag_stripe(data, start_x, start_y, 2);
}
