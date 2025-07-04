/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:35:40 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/28 18:35:33 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static void	fill_ray(t_data *data, t_ray *ray, t_vec *ray_dirvector)
{
	ray->raydir = ray_dirvector;
	ray->current_cell->xd = (int) data->player_pos->xd;
	ray->current_cell->yd = (int) data->player_pos->yd;
	if (ray->raydir->xd == 0)
		ray->delta->xd = __DBL_MAX__;
	else
		ray->delta->xd = fabs(1 / ray->raydir->xd);
	if (ray->raydir->yd == 0)
		ray->delta->yd = __DBL_MAX__;
	ray->delta->yd = fabs(1 / ray->raydir->yd);
	ray->side_dist->xd = 0;
	ray->side_dist->yd = 0;
	ray->step_cell->xd = 0;
	ray->step_cell->yd = 0;
	ray->has_hit = false;
	ray->check_cell = NULL;
}

void	cub_init_ray(t_data *data, t_vec *ray_dirvector)
{
	data->ray = ft_calloc(1, sizeof(t_ray));
	if (!data->ray)
		cub_handle_fatal(data, "Error\n init ray");
	data->ray->current_cell = cub_init_vec_double(0, 0);
	data->ray->step_cell = cub_init_vec_double(0, 0);
	data->ray->delta = cub_init_vec_double(0, 0);
	data->ray->side_dist = cub_init_vec_double(0, 0);
	if (!data->ray->current_cell || !data->ray->step_cell || !data->ray->delta \
|| !data->ray->side_dist)
		cub_handle_fatal(data, MSG_ALLOC);
	data->ray->prev_elem = -1;
	fill_ray(data, data->ray, ray_dirvector);
}

void	reinit_ray(t_data *data, t_vec *ray_dirvector)
{
	fill_ray(data, data->ray, ray_dirvector);
	data->ray->deg_from_dir = ft_get_angle_between_vec(ray_dirvector, \
data->cam->dir);
	data->ray->has_hit = false;
}
