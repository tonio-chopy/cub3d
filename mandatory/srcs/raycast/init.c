/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:25:46 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/29 14:33:01 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	init_ray_delta_values(t_ray *ray)
{
	if (ray->raydir->xd == 0)
		ray->delta->xd = __DBL_MAX__;
	else
		ray->delta->xd = fabs(1 / ray->raydir->xd);
	if (ray->raydir->yd == 0)
		ray->delta->yd = __DBL_MAX__;
	else
		ray->delta->yd = fabs(1 / ray->raydir->yd);
}

static void	init_ray_default_values(t_ray *ray)
{
	ray->side_dist->xd = 0;
	ray->side_dist->yd = 0;
	ray->step_cell->x = 0;
	ray->step_cell->y = 0;
	ray->has_hit = false;
	ray->wall_ratio = 0.0;
	ray->side = 'x';
	ray->deg_from_dir = 0.0;
	ray->pro_dist = 0.0;
	ray->pro_height = 0.0;
	ray->hit_dir = NORTH;
}

static void	fill_ray(t_data *data, t_ray *ray, t_vec *ray_dirvector)
{
	if (ray->raydir)
		free(ray->raydir);
	ray->raydir = cub_init_vec_double(ray_dirvector->xd, ray_dirvector->yd);
	if (!ray->raydir)
		cub_handle_fatal(data, "error init ray direction");
	ray->current_cell->x = (int) data->cam->orig->xd;
	ray->current_cell->y = (int) data->cam->orig->yd;
	init_ray_delta_values(ray);
	init_ray_default_values(ray);
}

void	cub_init_ray(t_data *data, t_vec *ray_dirvector)
{
	data->ray = ft_calloc(1, sizeof(t_ray));
	if (!data->ray)
		cub_handle_fatal(data, "error init ray");
	data->ray->raydir = NULL;
	data->ray->current_cell = cub_init_vec(0, 0);
	data->ray->step_cell = cub_init_vec(0, 0);
	data->ray->delta = cub_init_vec_double(0, 0);
	data->ray->side_dist = cub_init_vec_double(0, 0);
	data->ray->check_cell = NULL;
	if (!data->ray->current_cell || !data->ray->step_cell || !data->ray->delta \
|| !data->ray->side_dist)
		cub_handle_fatal(data, "error init ray components");
	fill_ray(data, data->ray, ray_dirvector);
}

void	reinit_ray(t_data *data, t_vec *ray_dirvector)
{
	fill_ray(data, data->ray, ray_dirvector);
	data->ray->deg_from_dir = ft_get_angle_between_vec(ray_dirvector, \
data->cam->dir);
	data->ray->has_hit = false;
}
