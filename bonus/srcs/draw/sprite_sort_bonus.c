/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_sort_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:57:51 by fpetit            #+#    #+#             */
/*   Updated: 2025/07/03 21:00:25 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	swap_sprites(t_sprite *s1, t_sprite *s2)
{
	t_sprite	temp;

	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void	cub_sort_sprites_dist_desc(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->nb_ball)
	{
		j = 0;
		while (j < data->nb_ball - i - 1)
		{
			if (data->balls[j]->distance < data->balls[j + 1]->distance)
				swap_sprites(data->balls[j], data->balls[j + 1]);
			j++;
		}
		i++;
	}
}

void	cub_draw_balls(t_data *data)
{
	int		i;
	double	px;
	double	py;
	double	bx;
	double	by;

	i = 0;
	while (i < data->nb_ball)
	{
		px = data->player_pos->xd;
		py = data->player_pos->yd;
		bx = data->balls[i]->pos->xd;
		by = data->balls[i]->pos->yd;
		data->balls[i]->distance = ((px - bx) * (px - bx) \
+ (py - by) * (py - by));
		i++;
	}
	cub_sort_sprites_dist_desc(data);
	i = 0;
	while (i < data->nb_ball)
	{
		cub_draw_sprite(data, data->balls[i]);
		i++;
	}
}
