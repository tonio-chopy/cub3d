/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:34:57 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/17 16:56:53 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	init_random(void)
{
	static int	initialized = 0;

	if (!initialized)
	{
		srand((unsigned int)time(NULL));
		initialized = 1;
	}
}

int	random_jump_side(void)
{
	init_random();
	return (rand() & 1);
}

void	handle_shoot(t_data *data, int key)
{
	bool	is_left_shoot;
	bool	is_left_jump;

	if (data->goal->win)
		return ;
	if (data->goal->has_shot == false && (key == XK_z || key == XK_c))
	{
		data->goal->has_shot = true;
		is_left_jump = random_jump_side();
		is_left_shoot = key == XK_z;
		if (is_left_jump)
			data->goal->position = GOAL_LEFT;
		else
			data->goal->position = GOAL_RIGHT;
		if (is_left_jump == is_left_shoot)
			data->goal->has_catched = true;
		else
		{
			data->goal->has_catched = false;
			data->goal->score++;
		}
	}
	if (data->goal->score == 2)
	{
		data->goal->win = true;
		data->goal->position = NONE;
	}
}
