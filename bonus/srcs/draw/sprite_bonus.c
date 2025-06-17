/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:34:31 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/17 16:37:04 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_bonus.h"

void	cub_draw_ball(t_data *data)
{
	int		ball_i;
	t_vec	*ball_pos;
	t_vec	ball_dist;
	t_vec	relative_pos;
	double	invdet;
	int		x;
	int		y;
	int		texx;
	int		texy;
	// int		d;
	int		color;
	int		index;

	data->goal->can_see_ball = false;
	if (data->goal->has_shot || data->goal->win)
		return ;
	ball_i = ft_strchri(data->parsed_map->elems, E_BALL);
	ball_pos = cub_get_coord_from_index(data, ball_i);
	ball_pos->xd += 0.5;
	ball_pos->yd += 0.5;
	ball_dist.xd = ball_pos->xd - data->player_pos->xd;
	ball_dist.yd = ball_pos->yd - data->player_pos->yd;
	free(ball_pos);
	data->sprite->distance = sqrt(ball_dist.xd * ball_dist.xd \
		+ ball_dist.yd * ball_dist.yd);
	if (data->sprite->distance < 0.5)
		return ;
	invdet = 1.0 / (data->cam->plane->xd * data->cam->dir->yd \
		- data->cam->dir->xd * data->cam->plane->yd);
	relative_pos.xd = invdet * (data->cam->dir->yd * ball_dist.xd \
		- data->cam->dir->xd * ball_dist.yd);
	relative_pos.yd = invdet * (-data->cam->plane->yd * ball_dist.xd \
		+ data->cam->plane->xd * ball_dist.yd);
	if (relative_pos.yd <= 0)
		return ;
	data->sprite->screenx = (int) (((double) WIN_W * 0.5) \
		* (1.0 + relative_pos.xd / relative_pos.yd));
	data->sprite->sprite_size = abs((int) (WIN_H / relative_pos.yd));
	data->sprite->uncutx = data->sprite->screenx - data->sprite->sprite_size / 2;
	data->sprite->uncutxend = data->sprite->screenx \
		+ data->sprite->sprite_size / 2;
	if (data->sprite->uncutx >= WIN_W || data->sprite->uncutxend < 0)
		return ;
	data->goal->can_see_ball = true;
	data->sprite->uncuty = (WIN_H / 2 - data->sprite->sprite_size / 2);
	data->sprite->uncutyend = (WIN_H / 2 + data->sprite->sprite_size / 2);
	data->sprite->drawstartx = data->sprite->uncutx;
	data->sprite->drawendx = data->sprite->uncutxend;
	data->sprite->drawstarty = data->sprite->uncuty;
	data->sprite->drawendy = data->sprite->uncutyend;
	if (data->sprite->drawstarty < 0)
		data->sprite->drawstarty = 0;
	if (data->sprite->drawendy >= WIN_H)
		data->sprite->drawendy = WIN_H - 1;
	if (data->sprite->drawstartx < 0)
		data->sprite->drawstartx = 0;
	if (data->sprite->drawendx >= WIN_W)
		data->sprite->drawendx = WIN_W - 1;
	x = data->sprite->drawstartx;
	if (data->goal->can_see_ball && data->goal->can_see_goal \
		&& !data->goal->has_shot)
		data->goal->can_shoot = true;
	index = data->goal->ball_anim_count / 10;
	while (x < data->sprite->drawendx)
	{
		if (data->sprite->distance < data->zbuffer[x] - 0.1f)
		{
			texx = (int) (BALL_SIZE * (x - data->sprite->uncutx) \
				/ (float) data->sprite->sprite_size);
			if (texx < 0)
				texx = 0;
			if (texx >= BALL_SIZE)
				texx = BALL_SIZE - 1;
			y = data->sprite->drawstarty;
			while (y < data->sprite->drawendy)
			{
				texy = (int) (BALL_SIZE * (y - data->sprite->uncuty) \
					/ data->sprite->sprite_size);
				if (texy < 0)
					texy = 0;
				if (texy >= BALL_SIZE)
					texy = BALL_SIZE - 1;
				color = data->sprites[index][texy * BALL_SIZE + texx];
				if (color != INVISIBLE)
					cub_put_pix_to_img(data->walls->img, x, y, color);
				y++;
			}
		}
		x++;
	}
}