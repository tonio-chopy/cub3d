/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/19 20:37:02 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	fill_ray(t_data *data, t_ray *ray, t_vec *ray_dirvector)
{
	ray->raydir = ray_dirvector;
	ray->current_cell->x = (int) data->cam->orig->xd;
	ray->current_cell->y = (int) data->cam->orig->yd;
	if (ray->raydir->xd == 0)
		ray->delta->xd = __DBL_MAX__;
	else
		ray->delta->xd = fabs(1 / ray->raydir->xd);
	if (ray->raydir->yd == 0)
		ray->delta->yd = __DBL_MAX__;
	ray->delta->yd = fabs(1 / ray->raydir->yd);
	ray->side_dist->xd = 0;
	ray->side_dist->yd = 0;
	ray->step_cell->x = 0;
	ray->step_cell->y = 0;
	ray->has_hit = false;
}

void	cub_init_ray(t_data *data, t_vec *ray_dirvector)
{
	t_ray	*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	if (!ray)
		cub_handle_fatal(data, "error init ray\n");
	ray->current_cell = cub_init_vec(0, 0);
	ray->step_cell = cub_init_vec(0, 0);
	ray->delta = cub_init_vec_double(0, 0);
	ray->side_dist = cub_init_vec_double(0, 0);
	fill_ray(data, ray, ray_dirvector);
	data->ray = ray;
}

void	reinit_ray(t_data *data, t_vec *ray_dirvector)
{
	fill_ray(data, data->ray, ray_dirvector);
	data->ray->deg_from_dir = ft_get_angle_between_vec(ray_dirvector, \
data->cam->dir);
	data->ray->has_hit = false;
}
