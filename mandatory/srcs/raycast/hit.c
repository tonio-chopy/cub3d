/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:27:47 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/25 16:25:39 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	cub_has_hit(t_data *data, t_ray *ray)
{
	char	elem;
	int		index;

	if (ray->current_cell->x < 0 || ray->current_cell->y < 0
		|| ray->current_cell->x >= data->parsed_map->width
		|| ray->current_cell->y >= data->parsed_map->heigth)
	{
		ray->has_hit = true;
		return ;
	}
	index = ray->current_cell->y
		* data->parsed_map->width + ray->current_cell->x;
	if (index < 0 || index >= data->parsed_map->nb_elems)
	{
		ray->has_hit = true;
		return ;
	}
	elem = data->parsed_map->elems[index];
	if (elem == E_WALL)
		ray->has_hit = true;
}

void	cub_iter_ray(t_data *data, t_ray *ray)
{
	while (!ray->has_hit)
	{
		if (ray->side_dist->xd < ray->side_dist->yd)
		{
			ray->side_dist->xd += ray->delta->xd;
			ray->current_cell->x += ray->step_cell->x;
			ray->side = 'x';
		}
		else
		{
			ray->side_dist->yd += ray->delta->yd;
			ray->current_cell->y += ray->step_cell->y;
			ray->side = 'y';
		}
		cub_has_hit(data, ray);
	}
}
