#include "test.h"

static void	compute_increments(t_ray *ray, t_vec *player)
{
	if (ray->raydir->xd < 0)
	{
		ray->step_cell->x = -1;
		ray->side_dist->xd = (player->xd - (double) ray->current_cell->x) \
* ray->delta->xd;
	}
	else
	{
		ray->step_cell->x = 1;
		ray->side_dist->xd = ((double) ray->current_cell->x \
+ 1.0 - player->xd) * ray->delta->xd;
	}
	if (ray->raydir->yd < 0)
	{
		ray->step_cell->y = -1;
		ray->side_dist->yd = (player->yd - (double) ray->current_cell->y) \
* ray->delta->yd;
	}
	else
	{
		ray->step_cell->y = 1;
		ray->side_dist->yd = ((double) ray->current_cell->y + 1.0 \
- player->yd) * ray->delta->yd;
	}
}

static double	compute_dist(t_data *data, t_ray *ray, char side)
{
	double	dist;

	if (side == 'x')
	{
		dist = ((double) ray->current_cell->x - data->player_pos->xd \
+ (1 - ray->step_cell->x) / 2) / ray->raydir->xd;
		ray->wall_ratio = data->player_pos->yd + dist * ray->raydir->yd;
	}
	else
	{
		dist = ((double) ray->current_cell->y - data->player_pos->yd \
+ (1 - ray->step_cell->y) / 2) / ray->raydir->yd;
		ray->wall_ratio = data->player_pos->xd + dist * ray->raydir->xd;
	}
	ray->wall_ratio -= floor(ray->wall_ratio);
	return (dist);
}

void	cub_has_hit(t_data *data, t_ray *ray)
{
	char	elem;

	elem = data->parsed_map->elems[ray->current_cell->y \
* data->parsed_map->width + ray->current_cell->x];
	if (elem == E_WALL || elem == E_GOAL_LEFT || elem == E_GOAL_CENTER || elem == E_GOAL_RIGHT)
		ray->has_hit = true;
}

static void	cub_iter_ray(t_data *data, t_ray *ray)
{
	int	index;

	while (!ray->has_hit)
	{
		if (ray->side_dist->xd < ray->side_dist->yd)
		{
			if (data->debug == 'v')
				printf("adjusting x by delta %f and moving to cell at %d \n", \
ray->delta->xd, ray->step_cell->x);
			ray->side_dist->xd += ray->delta->xd;
			ray->current_cell->x += ray->step_cell->x;
			ray->side = 'x';
		}
		else
		{
			if (data->debug == 'v')
				printf("adjusting y by delta %f and moving to cell at %d \n", \
ray->delta->yd, ray->step_cell->y);
			ray->side_dist->yd += ray->delta->yd;
			ray->current_cell->y += ray->step_cell->y;
			ray->side = 'y';
		}
		index = ray->current_cell->y * data->parsed_map->width \
+ ray->current_cell->x;
		cub_has_hit(data, ray);
	}
}

double	cub_measure_dist_to_wall(t_data *data, t_vec *ray_dirvector)
{
	double	distance;

	distance = -1;
	reinit_ray(data, ray_dirvector);
	compute_increments(data->ray, data->player_pos);
	if (data->debug == 'v')
		debug_ray(data->ray);
	cub_iter_ray(data, data->ray);
	distance = compute_dist(data, data->ray, data->ray->side);
	return (distance);
}
