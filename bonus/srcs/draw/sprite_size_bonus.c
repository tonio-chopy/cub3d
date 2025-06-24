/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_size_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:34:31 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/24 12:32:37 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void cub_compute_sprite_dist(t_data *data, t_vec *dist, char elem, t_sprite *sprite)
{
	int ball_i;
	t_vec *pos;

	ball_i = ft_strchri(data->parsed_map->elems, elem);
	if (elem == E_GOAL_CENTER)
		ball_i = data->parsed_map->opened_door_index;
	pos = cub_get_coord_from_index(data, ball_i);
	if (!pos)
		cub_handle_fatal(data, MSG_ALLOC);
	printf("player pos x %f y %f\n", data->player_pos->xd, data->player_pos->yd);
	pos->xd += 0.5;
	pos->yd += 0.5;
	dist->xd = pos->xd - data->player_pos->xd;
	dist->yd = pos->yd - data->player_pos->yd;
	free(pos);
	sprite->distance = sqrt(dist->xd * dist->xd + dist->yd * dist->yd);
	if (elem == E_GOAL_CENTER)
		printf("sprite dist is %f\n", sprite->distance);
}

void cub_compute_cup_size(t_data *data, int *code, char elem)
{
	double invdet;
	t_vec relative_pos;
	t_vec cup_dist;

	*code = 1;
	cub_compute_sprite_dist(data, &cup_dist, elem, data->cup);
	if (elem == E_CUP && data->cup->distance < 0.01)
		return;
	invdet = 1.0 / (data->cam->plane->xd * data->cam->dir->yd - data->cam->dir->xd * data->cam->plane->yd);
	relative_pos.xd = invdet * (data->cam->dir->yd * cup_dist.xd - data->cam->dir->xd * cup_dist.yd);
	relative_pos.yd = invdet * (-data->cam->plane->yd * cup_dist.xd + data->cam->plane->xd * cup_dist.yd);
	if (relative_pos.yd <= 0)
		return;
	data->cup->screenx = (int)(((double)WIN_W * 0.5) * (1.0 + relative_pos.xd / relative_pos.yd));
	data->cup->sprite_size = abs((int)(WIN_H / relative_pos.yd));
	*code = 0;
}

void cub_compute_ball_size(t_data *data, int *code, char elem)
{
	double invdet;
	t_vec relative_pos;
	t_vec ball_dist;

	*code = 1;
	cub_compute_sprite_dist(data, &ball_dist, elem, data->ball);
	if (elem == E_BALL && data->ball->distance < 0.2)
		return;
	invdet = 1.0 / (data->cam->plane->xd * data->cam->dir->yd - data->cam->dir->xd * data->cam->plane->yd);
	relative_pos.xd = invdet * (data->cam->dir->yd * ball_dist.xd - data->cam->dir->xd * ball_dist.yd);
	relative_pos.yd = invdet * (-data->cam->plane->yd * ball_dist.xd + data->cam->plane->xd * ball_dist.yd);
	if (relative_pos.yd <= 0)
		return;
	data->ball->screenx = (int)(((double)WIN_W * 0.5) * (1.0 + relative_pos.xd / relative_pos.yd));
	data->ball->sprite_size = abs((int)(WIN_H / relative_pos.yd));
	*code = 0;
}
