/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 16:23:01 by fpetit            #+#    #+#             */
/*   Updated: 2025/07/05 16:53:42 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

double	cub_measure_dist_to_opened_door(t_data *data, t_vec *ray_dirvector)
{
	return (cub_measure_dist_to_wall(data, ray_dirvector));
}

void	handle_open(t_data *data, int key)
{
	int		elem_index;
	double	diffx;
	double	diffy;
	double	distance;
	t_vec	*door;

	if (data->goal->win && key == XK_o)
	{
		elem_index = ft_strchri(data->parsed_map->elems, E_GOAL_CENTER);
		door = cub_get_center_coord_from_index(data, elem_index);
		if (!door)
			cub_handle_fatal(data, MSG_ALLOC);
		diffx = data->player_pos->xd - door->xd;
		diffy = data->player_pos->yd - door->yd;
		free(door);
		distance = sqrt(diffx * diffx + diffy * diffy);
		if (distance < 2)
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
	double	diffx;
	double	diffy;
	t_vec	*door;

	if (key == XK_p && data->parsed_map->opened_door_index != -1)
	{
		door = cub_get_center_coord_from_index(data, \
data->parsed_map->opened_door_index);
		if (!door)
			cub_handle_fatal(data, MSG_ALLOC);
		diffx = data->player_pos->xd - door->xd;
		diffy = data->player_pos->yd - door->yd;
		free(door);
		distance = sqrt(diffx * diffx + diffy * diffy);
		if (distance != -1 && distance < 1.5f)
		{
			data->parsed_map->elems[data->parsed_map->opened_door_index] \
= E_GOAL_CENTER;
			data->parsed_map->opened_door_index = -1;
		}
	}
}
