/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:34:31 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/24 12:35:51 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_adjust_sprite_for_screen(t_data *data, t_sprite *sprite, int *code)
{
	*code = EXIT_FAILURE;
	sprite->uncutx = sprite->screenx \
- sprite->sprite_size / 2;
	sprite->uncutxend = sprite->screenx \
+ sprite->sprite_size / 2;
	if (sprite->uncutx >= WIN_W || sprite->uncutxend < 0)
		return ;
	data->goal->can_see_ball = true;
	sprite->uncuty = (WIN_H / 2 - sprite->sprite_size / 2);
	sprite->uncutyend = (WIN_H / 2 + sprite->sprite_size / 2);
	sprite->drawstartx = sprite->uncutx;
	sprite->drawendx = sprite->uncutxend;
	sprite->drawstarty = sprite->uncuty;
	sprite->drawendy = sprite->uncutyend;
	if (sprite->drawstarty < 0)
		sprite->drawstarty = 0;
	if (sprite->drawendy >= WIN_H)
		sprite->drawendy = WIN_H - 1;
	if (sprite->drawstartx < 0)
		sprite->drawstartx = 0;
	if (sprite->drawendx >= WIN_W)
		sprite->drawendx = WIN_W - 1;
	*code = EXIT_SUCCESS;
}

void	cub_draw_ball_vline(t_data *data, int texx, int x, int *y)
{
	int		color;	
	int		texy;

	texy = (int)(BALL_SIZE * (*y - data->ball->uncuty) \
/ data->ball->sprite_size);
	if (texy < 0)
		texy = 0;
	if (texy >= BALL_SIZE)
		texy = BALL_SIZE - 1;
	color = data->ball->sprites[data->ball->sprite_index][texy * BALL_SIZE + texx];
	if (color != INVISIBLE)
		cub_put_pix_to_img(data->walls->img, x, *y, color);
	(*y)++;
}

void	cub_draw_cup_vline(t_data *data, int texx, int x, int *y)
{
	int		color;	
	int		texy;

	texy = (int)(CUP_SIZE * (*y - data->cup->uncuty) \
/ data->cup->sprite_size);
	if (texy < 0)
		texy = 0;
	if (texy >= CUP_SIZE)
		texy = CUP_SIZE - 1;
	color = data->cup->sprites[data->cup->sprite_index][texy * CUP_SIZE + texx];
	if (color != INVISIBLE)
		cub_put_pix_to_img(data->walls->img, x, *y, color);
	(*y)++;
}

void	cub_draw_ball_lines(t_data *data)
{
	int		x;
	int		y;
	int		texx;

	x = data->ball->drawstartx;
	data->ball->sprite_index = data->goal->ball_anim_count / 10;
	// printf("sprite index %d\n", data->goal->sprite_index);
	while (x < data->ball->drawendx)
	{
		if (data->ball->distance < data->zbuffer[x] - 0.1f)
		{
			texx = (int)(BALL_SIZE * (x - data->ball->uncutx) \
/ (float) data->ball->sprite_size);
			if (texx < 0)
				texx = 0;
			if (texx >= BALL_SIZE)
				texx = BALL_SIZE - 1;
			y = data->ball->drawstarty;
			while (y < data->ball->drawendy)
				cub_draw_ball_vline(data, texx, x, &y);
		}
		x++;
	}
}

void	cub_draw_cup_lines(t_data *data)
{
	int		x;
	int		y;
	int		texx;

	x = data->cup->drawstartx;
	data->cup->sprite_index = data->goal->cup_anim_count / 10;
	while (x < data->cup->drawendx)
	{
		if (data->cup->distance < data->zbuffer[x] - 0.1f)
		{
			texx = (int)(CUP_SIZE * (x - data->cup->uncutx) \
/ (float) data->cup->sprite_size);
			if (texx < 0)
				texx = 0;
			if (texx >= CUP_SIZE)
				texx = CUP_SIZE - 1;
			y = data->cup->drawstarty;
			while (y < data->cup->drawendy)
				cub_draw_cup_vline(data, texx, x, &y);
		}
		x++;
	}
}

void	cub_draw_ball(t_data *data)
{
	int		code;

	if (data->goal->has_shot || data->goal->win)
		return ;
	cub_compute_ball_size(data, &code, E_BALL);
	if (code == 1)
		return ;
	cub_adjust_sprite_for_screen(data, data->ball, &code);
	if (code == 1)
		return ;
	if (data->goal->can_see_ball && data->goal->can_see_goal \
&& !data->goal->has_shot)
		data->goal->can_shoot = true;
	cub_draw_ball_lines(data);
}

void	cub_draw_cup(t_data *data)
{
	int	code;

	if (!data->goal->win)
		return ;
	cub_compute_cup_size(data, &code, E_GOAL_CENTER);
	if (code == 1)
		return ;
	cub_adjust_sprite_for_screen(data, data->cup, &code);
	if (code == 1)
		return ;
	cub_draw_cup_lines(data);
}