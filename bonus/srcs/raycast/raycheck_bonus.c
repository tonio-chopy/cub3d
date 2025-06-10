/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycheck_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:35:47 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/10 15:36:12 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_bonus.h"

t_vec	*cub_get_coord_from_index(t_data *data, int index)
{
	t_vec	*vec;

	vec = cub_init_vec(index % data->parsed_map->width, index
			/ data->parsed_map->width);
	return (vec);
}

double	cub_measure_dist_to_opened_door(t_data *data, t_vec *ray_dirvector)
{
	double	distance;

	distance = -1;
	reinit_ray(data, ray_dirvector);
	data->ray->check_cell = cub_get_coord_from_index(data,
			data->parsed_map->opened_door_index);
	compute_increments(data->ray, data->player_pos);
	if (data->debug == '1')
		debug_ray(data->ray);
	cub_iter_ray(data, data->ray);
	distance = compute_dist(data, data->ray, data->ray->side);
	return (distance);
}
