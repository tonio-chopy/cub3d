/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:34:31 by fpetit            #+#    #+#             */
/*   Updated: 2025/07/05 12:01:59 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static	void	cub_transform_to_cam_space(t_data *data, t_sprite *sprite)
{
	int				index;
	double			relative_x;
	double			relative_y;
	double			inv_det;

	index = ft_strchri(data->parsed_map->elems, sprite->elem);
	if (index == -1)
		return ;
	if (sprite->elem == E_CUP)
		sprite->pos = cub_get_center_coord_from_index(data, index);
	relative_x = sprite->pos->xd - data->player_pos->xd;
	relative_y = sprite->pos->yd - data->player_pos->yd;
	inv_det = 1.0 / (data->cam->plane->xd * data->cam->dir->yd
			- data->cam->dir->xd * data->cam->plane->yd);
	sprite->transform_x = inv_det * (data->cam->dir->yd * relative_x
			- data->cam->dir->xd * relative_y);
	sprite->transform_y = inv_det * (-data->cam->plane->yd * relative_x
			+ data->cam->plane->xd * relative_y);
}

void	cub_adjust_sprite_dim(t_sprite *sprite)
{
	sprite->screenx = (int)(((double) WIN_W / 2.0) \
* (1.0 + (sprite->transform_x / sprite->transform_y)));
	sprite->height = abs((int)(WIN_H / sprite->transform_y));
	sprite->drawstarty = -sprite->height / 2 + WIN_H / 2;
	if (sprite->drawstarty < 0)
		sprite->drawstarty = 0;
	sprite->drawendy = sprite->height / 2 + WIN_H / 2;
	if (sprite->drawendy >= WIN_H)
		sprite->drawendy = WIN_H - 1;
	sprite->width = abs((int)(WIN_H / sprite->transform_y));
	sprite->width = abs((int)(WIN_H / sprite->transform_y));
	sprite->drawstartx = -sprite->width / 2 + sprite->screenx;
	if (sprite->drawstartx < 0)
		sprite->drawstartx = 0;
	sprite->drawendx = sprite->width / 2 + sprite->screenx;
	if (sprite->drawendx >= WIN_W)
		sprite->drawendx = WIN_W - 1;
}

void	cub_draw_vline(t_data *data, t_sprite *sprite, t_vec *tex, int x)
{
	int				y;
	int				d;
	unsigned int	color;

	y = sprite->drawstarty;
	while (y < sprite->drawendy)
	{
		d = y * CUP_SIZE - WIN_H
			* CUP_SIZE / 2 + sprite->height * CUP_SIZE / 2;
		tex->yd = ((d * CUP_SIZE) / sprite->height) / CUP_SIZE;
		color = get_sprite_pixel_color(data, sprite, tex->xd, tex->yd);
		if (color != INVISIBLE)
			cub_put_pix_to_img(data->walls->img, x, y, color);
		y++;
	}
}

void	cub_draw_sprite_lines(t_data *data, t_sprite *sprite)
{
	t_vec	tex;
	int		x;

	x = sprite->drawstartx;
	while (x < sprite->drawendx)
	{
		tex.xd = (int)(CUP_SIZE * (x - (-sprite->width / 2 + sprite->screenx)) \
* CUP_SIZE / sprite->width) / CUP_SIZE;
		if (sprite->transform_y > 0 && x > 0 && x < WIN_W
			&& sprite->transform_y < data->zbuffer[x])
		{
			cub_draw_vline(data, sprite, &tex, x);
		}
		x++;
	}
}

void	cub_draw_sprite(t_data *data, t_sprite *sprite)
{
	if (sprite->elem == E_BALL_VISITED && data->goal->has_shot)
		return ;
	if (sprite->elem == E_CUP && !data->goal->win)
		return ;
	cub_transform_to_cam_space(data, sprite);
	if (sprite->transform_y <= 0.1)
		return ;
	cub_adjust_sprite_dim(sprite);
	cub_draw_sprite_lines(data, sprite);
}
