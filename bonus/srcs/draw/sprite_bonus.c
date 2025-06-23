/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:34:31 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/23 17:27:49 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_adjust_sprite_for_screen(t_data *data, int *code)
{
	*code = EXIT_FAILURE;
	data->sprite->uncutx = data->sprite->screenx \
- data->sprite->sprite_size / 2;
	data->sprite->uncutxend = data->sprite->screenx \
+ data->sprite->sprite_size / 2;
	if (data->sprite->uncutx >= WIN_W || data->sprite->uncutxend < 0)
		return ;
	data->goal->can_see_ball = true;
	// printf("sprite size %d\n", data->sprite->sprite_size);
	data->sprite->uncuty = (WIN_H / 2 - data->sprite->sprite_size / 2);
	data->sprite->uncutyend = (WIN_H / 2 + data->sprite->sprite_size / 2);
	data->sprite->drawstartx = data->sprite->uncutx;
	data->sprite->drawendx = data->sprite->uncutxend;
	data->sprite->drawstarty = data->sprite->uncuty;
	data->sprite->drawendy = data->sprite->uncutyend;
	// printf("sprite start x %d\n", data->sprite->drawstartx);
	// printf("sprite start y %d\n", data->sprite->drawstarty);
	if (data->sprite->drawstarty < 0)
		data->sprite->drawstarty = 0;
	if (data->sprite->drawendy >= WIN_H)
		data->sprite->drawendy = WIN_H - 1;
	if (data->sprite->drawstartx < 0)
		data->sprite->drawstartx = 0;
	if (data->sprite->drawendx >= WIN_W)
		data->sprite->drawendx = WIN_W - 1;
	*code = EXIT_SUCCESS;
}

void	cub_draw_ball_vline(t_data *data, int texx, int x, int *y)
{
	int		color;	
	int		texy;

	texy = (int)(BALL_SIZE * (*y - data->sprite->uncuty) \
/ data->sprite->sprite_size);
	if (texy < 0)
		texy = 0;
	if (texy >= BALL_SIZE)
		texy = BALL_SIZE - 1;
	color = data->sprites[data->goal->sprite_index][texy * BALL_SIZE + texx];
	if (color != INVISIBLE)
		cub_put_pix_to_img(data->walls->img, x, *y, color);
	(*y)++;
}

void	cub_draw_ball_lines(t_data *data, t_target target)
{
	int		x;
	int		y;
	int		texx;

	x = data->sprite->drawstartx;
	if (target == CUP)
		data->goal->sprite_index = 5 + data->goal->cup_anim_count / 10;
	else if (target == BALL)
		data->goal->sprite_index = data->goal->ball_anim_count / 10;
	// printf("sprite index %d\n", data->goal->sprite_index);
	while (x < data->sprite->drawendx)
	{
		if (data->sprite->distance < data->zbuffer[x] - 0.1f)
		{
			texx = (int)(BALL_SIZE * (x - data->sprite->uncutx) \
/ (float) data->sprite->sprite_size);
			if (texx < 0)
				texx = 0;
			if (texx >= BALL_SIZE)
				texx = BALL_SIZE - 1;
			y = data->sprite->drawstarty;
			while (y < data->sprite->drawendy)
				cub_draw_ball_vline(data, texx, x, &y);
		}
		x++;
	}
}

// void	cub_draw_cup_lines(t_data *data)
// {
// 		int		x;
// 	int		y;
// 	int		texx;

// 	x = data->sprite->drawstartx;
// 	data->goal->sprite_index = data->goal->ball_anim_count / 10;
// 	while (x < data->sprite->drawendx)
// 	{
// 		if (data->sprite->distance < data->zbuffer[x] - 0.1f)
// 		{
// 			texx = (int)(BALL_SIZE * (x - data->sprite->uncutx) \
// / (float) data->sprite->sprite_size);
// 			if (texx < 0)
// 				texx = 0;
// 			if (texx >= BALL_SIZE)
// 				texx = BALL_SIZE - 1;
// 			y = data->sprite->drawstarty;
// 			while (y < data->sprite->drawendy)
// 				cub_draw_ball_vline(data, texx, x, &y);
// 		}
// 		x++;
// 	}
// }

void	cub_draw_ball(t_data *data)
{
	int		code;

	if (data->goal->has_shot || data->goal->win)
		return ;
	cub_compute_sprite_size(data, &code, E_BALL);
	if (code == 1)
		return ;
	cub_adjust_sprite_for_screen(data, &code);
	if (code == 1)
		return ;
	if (data->goal->can_see_ball && data->goal->can_see_goal \
&& !data->goal->has_shot)
		data->goal->can_shoot = true;
	cub_draw_ball_lines(data, BALL);
}

void	cub_draw_cup(t_data *data)
{
	int	code;

	if (!data->goal->win)
		return ;
	cub_compute_sprite_size(data, &code, E_GOAL_CENTER);
	if (code == 1)
		return ;
	cub_adjust_sprite_for_screen(data, &code);
	if (code == 1)
		return ;
	cub_draw_ball_lines(data, CUP);
}