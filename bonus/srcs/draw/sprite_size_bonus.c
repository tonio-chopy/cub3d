/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_size_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:34:31 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/17 18:25:09 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_compute_sprite_dist(t_data *data, t_vec *ball_dist)
{
	int		ball_i;
	t_vec	*ball_pos;

	ball_i = ft_strchri(data->parsed_map->elems, E_BALL);
	ball_pos = cub_get_coord_from_index(data, ball_i);
	if (!ball_pos)
		cub_handle_fatal(data, MSG_ALLOC);
	ball_pos->xd += 0.5;
	ball_pos->yd += 0.5;
	ball_dist->xd = ball_pos->xd - data->player_pos->xd;
	ball_dist->yd = ball_pos->yd - data->player_pos->yd;
	free(ball_pos);
	data->sprite->distance = sqrt(ball_dist->xd * ball_dist->xd \
+ ball_dist->yd * ball_dist->yd);
}

void	cub_compute_sprite_size(t_data *data, int *code)
{
	double	invdet;
	t_vec	relative_pos;
	t_vec	ball_dist;

	*code = 1;
	cub_compute_sprite_dist(data, &ball_dist);
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
	data->sprite->screenx = (int)(((double) WIN_W * 0.5) \
* (1.0 + relative_pos.xd / relative_pos.yd));
	data->sprite->sprite_size = abs((int)(WIN_H / relative_pos.yd));
	*code = 0;
}
