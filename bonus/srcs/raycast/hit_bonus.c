/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:27:47 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/19 20:35:22 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_has_hit(t_data *data, t_ray *ray)
{
	char	elem;

	elem = data->parsed_map->elems[ray->current_cell->y
		* data->parsed_map->width + ray->current_cell->x];
	if (ray->check_cell)
	{
		if ((int)ray->check_cell->xd == ray->current_cell->x
			&& (int)ray->check_cell->yd == ray->current_cell->y)
		{
			ray->has_hit = true;
			return ;
		}
	}
	if (elem == E_WALL || elem == E_GOAL_LEFT \
|| elem == E_GOAL_CENTER || elem == E_GOAL_RIGHT)
		ray->has_hit = true;
	if (elem == E_GOAL_LEFT || elem == E_GOAL_CENTER || elem == E_GOAL_RIGHT)
		data->goal->can_see_goal = true;
}

void	cub_iter_ray(t_data *data, t_ray *ray)
{
	int	index;

	while (!ray->has_hit && ray->current_cell->x >= 0 \
&& ray->current_cell->y >= 0
	)
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
		index = ray->current_cell->y * data->parsed_map->width
			+ ray->current_cell->x;
		cub_has_hit(data, ray);
	}
}