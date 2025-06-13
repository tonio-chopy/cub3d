/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:34:31 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/13 18:01:24 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_bonus.h"

void	cub_transform_pos(t_data *data, t_vec *ball_pos)
{
	double	inverseDeterminant;
	t_vec	*dir;
	t_vec	*plane;
	double	tr_x;
	double	tr_y;

	dir = data->cam->dir;
	plane = data->cam->plane;
	inverseDeterminant = 1.0 / (data->cam->plane->xd * data->cam->dir->yd \
- data->cam->dir->xd * data->cam->plane->yd);
	tr_x = inverseDeterminant * (dir->yd * ball_pos->xd - dir->xd * ball_pos->yd);
	tr_y = inverseDeterminant * (- plane->yd * ball_pos->xd - plane->xd * ball_pos->yd);
	ball_pos->xd = tr_x;
	ball_pos->yd = tr_y;
}

t_vec	*get_start(int height, int width, int sprite_x)
{
	t_vec *start;

	start = cub_init_vec(0, 0);
	start->x = -width / 2 + sprite_x;
	start->y = -height / 2 + WIN_H / 2;
	return (start);
}

t_vec	*get_end(int height, int width, int sprite_x)
{
	t_vec	*end;

	end = cub_init_vec(0, 0);
	end->x = width / 2 + sprite_x;
	end->y = height / 2 + WIN_H / 2;
	return (end);
}

void	cub_draw_vline(t_data *data, t_vec *start, t_vec *end, int texx)
{
	int	y;
	int	pos;
	int	texy;
	int	sprite_index;
	int	color;

	y = start->y;
	while (y < end->y)
	{
		pos = y * 256 - WIN_H * 128 + data->ball_h * 128;
		texy = pos * BALL_SIZE / data->ball_h / 256;
		sprite_index = data->goal->ball_anim_count / 5;
		color = data->sprites[sprite_index][BALL_SIZE * texy + texx];
		if (color != INVISIBLE)
			cub_put_pix_to_img(data->walls->img, (int) start->x, (int) y, color);
		y++;
	}
}

void	cub_draw_stripes(t_data *data)
{
	int	sprite_x;
	t_vec	*start;
	t_vec	*end;
	int	x;
	int	texx;

	sprite_x = (int) (WIN_W / 2) * (1 + data->ball_pos->xd / data->ball_pos->yd);
	data->ball_h = abs((int)(WIN_H / data->ball_pos->yd));
	data->ball_w = abs((int) (WIN_H / data->ball_pos->yd));
	start = get_start(data->ball_h, data->ball_w, sprite_x);
	end = get_end(data->ball_h, data->ball_w, sprite_x);
	x = start->x;
	while (x < end->x)
	{
		texx = (int) (256 * (x - (-data->ball_w / 2 + sprite_x)) * BALL_SIZE / data->ball_w) / 256;
		if (data->ball_pos->yd > 0 && x > 0 && x < WIN_H && data->ball_pos->yd < data->zbuffer[x])
		{
			cub_draw_vline(data, start, end, texx);
		}
		x++;
	}
}

void	cub_draw_ball(t_data *data)
{
	double	dist_x;
	double	dist_y;
	int		ball_i;

	ball_i = ft_strchri(data->parsed_map->elems, E_BALL);
	data->ball_pos = cub_get_centercoord_norm(data->parsed_map, ball_i);
	dist_x = data->ball_pos->xd - data->cam->orig->xd;
	dist_y = data->ball_pos->yd - data->cam->orig->yd;
	cub_transform_pos(data, data->ball_pos);
	cub_draw_stripes(data);
}
