/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_shapes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/28 16:26:43 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
		cub_put_pix_to_img(img, round(draw.xd), round(draw.yd), color);
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
			cub_put_pix_to_img_inv(img, round(x), round(y), rect->color);
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
