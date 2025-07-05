/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 20:27:47 by fpetit            #+#    #+#             */
/*   Updated: 2025/07/05 16:53:23 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_has_hit(t_data *data, t_ray *ray)
{
	char	elem;

	elem = data->parsed_map->elems[(int) ray->current_cell->yd
		* data->parsed_map->width + (int) ray->current_cell->xd];
	if (ray->check_cell)
	{
		if ((int)ray->check_cell->xd == ray->current_cell->xd
			&& (int)ray->check_cell->yd == ray->current_cell->yd)
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

	while (!ray->has_hit && ray->current_cell->xd >= 0 \
&& ray->current_cell->yd >= 0
	)
	{
		if (ray->side_dist->xd < ray->side_dist->yd)
		{
			ray->side_dist->xd += ray->delta->xd;
			ray->current_cell->xd += ray->step_cell->xd;
			ray->side = 'x';
		}
		else
		{
			ray->side_dist->yd += ray->delta->yd;
			ray->current_cell->yd += ray->step_cell->yd;
			ray->side = 'y';
		}
		if (ray->current_cell->yd < 0 || ray->current_cell->xd < 0)
			return ;
		index = (int) ray->current_cell->yd * data->parsed_map->width
			+ (int) ray->current_cell->xd;
		cub_has_hit(data, ray);
	}
}
