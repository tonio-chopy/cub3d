/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:34:57 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/10 17:52:34 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_bonus.h"

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

	// printf("in handle shoot\n is win = %d\n", data->goal->win);
	if (data->goal->win)
		return ;
	if (data->goal->has_shot == false && (key == XK_z || key == XK_c))
	{
		data->goal->has_shot = true;
		// printf("key is z or c\n");
		is_left_jump = random_jump_side();
		is_left_shoot = key == XK_z;
		// printf("is left shoot = %d\n", is_left_shoot);
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

void	handle_open(t_data *data, int key)
{
	double	distance;
	char	elem;
	int		elem_index;

	if (key == XK_o)
	{
		distance = cub_measure_dist_to_wall(data, data->cam->dir);
		elem_index = data->ray->current_cell->y * data->parsed_map->width
			+ data->ray->current_cell->x;
		elem = data->parsed_map->elems[elem_index];
		if (distance < 1.5f && elem == E_GOAL_CENTER)
		{
			data->parsed_map->elems[elem_index] = E_INSIDE;
			data->parsed_map->opened_door_index = elem_index;
		}
	}
}

void	handle_close(t_data *data, int key)
{
	double	distance;

	if (key == XK_p && data->parsed_map->opened_door_index != -1)
	{
		distance = cub_measure_dist_to_opened_door(data, data->cam->dir);
		if (distance != -1 && distance < 1.5f)
		{
			data->parsed_map->elems[data->parsed_map->opened_door_index] = E_GOAL_CENTER;
			data->parsed_map->opened_door_index = -1;
		}
	}
}
