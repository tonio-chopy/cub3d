/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:27:47 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/19 20:35:06 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	cub_has_hit(t_data *data, t_ray *ray)
{
	char	elem;

	elem = data->parsed_map->elems[ray->current_cell->y
		* data->parsed_map->width + ray->current_cell->x];
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