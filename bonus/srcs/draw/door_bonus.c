/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:23:01 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/24 16:14:23 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

double	cub_measure_dist_to_opened_door(t_data *data, t_vec *ray_dirvector)
{
	return (cub_measure_dist_to_wall(data, ray_dirvector));
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
		if (elem == E_GOAL_CENTER)
		{
			data->parsed_map->elems[elem_index] = E_INSIDE;
			if (data->goal->win)
				data->parsed_map->elems[elem_index] = E_CUP;
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
			data->parsed_map->elems[data->parsed_map->opened_door_index] \
= E_GOAL_CENTER;
			data->parsed_map->opened_door_index = -1;
		}
	}
}
