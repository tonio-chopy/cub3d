/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shoot.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:34:54 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/10 16:02:21 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_bonus.h"

// static int	random_position(void)
// {
// 	return (rand() % 3);
// }

// void	init_random(void)
// {
// 	srand(time(NULL));
// }

// void	handle_shoot(t_data *data, int key)
// {
// 	int	new_pos;

// 	if (key == 32)
// 	{
// 		if (data->goal->position == GOAL_CENTER && !data->goal->has_catched)
// 		{
// 			data->goal->has_catched = true;
// 			data->goal->score++;
// 			if (data->goal->score >= 5)
// 				data->goal->win = true;
// 		}
// 		else if (!data->goal->has_catched)
// 		{
// 			data->goal->has_catched = false;
// 		}
// 		new_pos = random_position();
// 		if (new_pos == 0)
// 			data->goal->position = GOAL_LEFT;
// 		else if (new_pos == 1)
// 			data->goal->position = GOAL_CENTER;
// 		else
// 			data->goal->position = GOAL_RIGHT;
// 		data->goal->has_catched = false;
// 	}
// }

// void	handle_open(t_data *data, int key)
// {
// 	t_vec	*front_cell;
// 	int		index;

// 	if (key == 111)
// 	{
// 		front_cell = cub_init_vec_double(data->player_pos->xd
// 				+ data->cam->dir->xd, data->player_pos->yd
// 				+ data->cam->dir->yd);
// 		if (front_cell->xd >= 0 && front_cell->xd < data->parsed_map->width
// 			&& front_cell->yd >= 0 && front_cell->yd < data->parsed_map->heigth)
// 		{
// 			index = (int)front_cell->yd * data->parsed_map->width
// 				+ (int)front_cell->xd;
// 			if (data->parsed_map->elems[index] == E_GOAL_LEFT
// 				|| data->parsed_map->elems[index] == E_GOAL_CENTER
// 				|| data->parsed_map->elems[index] == E_GOAL_RIGHT)
// 			{
// 				data->parsed_map->elems[index] = E_GOAL_OPENED;
// 				data->parsed_map->opened_door_index = index;
// 				data->ray->check_cell = cub_init_vec_double(front_cell->xd,
// 						front_cell->yd);
// 			}
// 		}
// 		free(front_cell);
// 	}
// }

// void	handle_close(t_data *data, int key)
// {
// 	if (key == 99)
// 	{
// 		if (data->parsed_map->opened_door_index != -1)
// 		{
// 			data->parsed_map->elems[data->parsed_map->opened_door_index] = E_GOAL_CENTER;
// 			data->parsed_map->opened_door_index = -1;
// 			if (data->ray->check_cell)
// 			{
// 				free(data->ray->check_cell);
// 				data->ray->check_cell = NULL;
// 			}
// 		}
// 	}
// }

double	cub_measure_dist_to_opened_door(t_data *data, t_vec *ray_dirvector)
{
	return (cub_measure_dist_to_wall(data, ray_dirvector));
}
