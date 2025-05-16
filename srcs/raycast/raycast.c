#include "test.h"

static void	compute_increments(t_ray *ray, t_vec *player)
{
	if (ray->raydir->xd < 0)
	{
		ray->step_cell->x = -1;
		ray->side_dist->xd = (player->xd - (double) ray->current_cell->x) * ray->delta->xd;
	}
	else
	{
		ray->step_cell->x = 1;
		ray->side_dist->xd = ((double) ray->current_cell->x + 1.0 - player->xd) * ray->delta->xd;
	}
	if (ray->raydir->yd < 0)
	{
		ray->step_cell->y = -1;
		ray->side_dist->yd = (player->yd - (double) ray->current_cell->y) * ray->delta->yd;
	}
	else
	{
		ray->step_cell->y = 1;
		ray->side_dist->yd = ((double) ray->current_cell->y + 1.0 - player->yd) * ray->delta->yd;
	}
	// printf("first side dist is x %f y%f \n", ray->side_dist->xd, ray->side_dist->yd);
}

static double	compute_dist(t_data *data, t_ray *ray, char side)
{
	double dist;

	if (side == 'x')
	{
		dist = ((double) ray->current_cell->x - data->player_pos->xd + (1 - ray->step_cell->x) / 2) / ray->raydir->xd;
		ray->wall_ratio = data->player_pos->yd + dist * ray->raydir->yd; 
	}
	else
	{
		dist = ((double) ray->current_cell->y - data->player_pos->yd + (1 - ray->step_cell->y) / 2) / ray->raydir->yd;
        ray->wall_ratio = data->player_pos->xd + dist * ray->raydir->xd; 
	}
	ray->wall_ratio -= floor(ray->wall_ratio);
	return (dist);
}

static void	cub_iter_ray(t_data *data, t_ray *ray)
{
	while (!ray->has_hit)
	{
		if (ray->side_dist->xd < ray->side_dist->yd)
		{
			if (data->debug == 'v')
				printf("adjusting x by delta %f and moving to cell at %d \n", ray->delta->xd, ray->step_cell->x);
			ray->side_dist->xd += ray->delta->xd;
			ray->current_cell->x += ray->step_cell->x;
			ray->side = 'x';
		}
		else
		{
			if (data->debug == 'v')	
				printf("adjusting y by delta %f and moving to cell at %d \n", ray->delta->yd, ray->step_cell->y);
			ray->side_dist->yd += ray->delta->yd;
			ray->current_cell->y += ray->step_cell->y;
			ray->side = 'y';
		}
		int index = ray->current_cell->y * data->parsed_map->width + ray->current_cell->x;
		if (data->debug == 'v')
		{
			printf("now at index %d (y %d and x %d) .. checking for wall\n", index, ray->current_cell->y, ray->current_cell->x);
			printf("elem at index = %c\n", data->parsed_map->elems[index]);
		}		
		if (data->parsed_map->elems[ray->current_cell->y * data->parsed_map->width + ray->current_cell->x] == E_WALL)
			ray->has_hit = true;
	}
}

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
	t_ray *ray;

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
	data->ray->deg_from_dir = ft_get_angle_between_vec(ray_dirvector, data->cam->dir);
	data->ray->has_hit = false;
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