#include "test.h"

void	cub_put_pix_to_img(t_img *img, int x, int y, unsigned int color)
{
	char	*pixel;
	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		pixel = img->addr + (int) (y * img->line_length + x * (img->bpp / 8));
			*(unsigned int *) pixel = color;
	}
}

void	compute_increments(t_ray *ray, t_point *player)
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
}

double	compute_dist(t_data *data, t_ray *ray, char side)
{
	double dist;

	if (side == 'x')
	{
		dist = ((double) ray->current_cell->x - data->player_pos->xd + (1 - ray->step_cell->x) / 2) / ray->raydir->xd;
	}
	else
		dist = ((double) ray->current_cell->y - data->player_pos->yd + (1 - ray->step_cell->y) / 2) / ray->raydir->yd;
	return (dist);
}

double	measure_dist_to_wall(t_data *data, t_point *ray_dirvector, t_point *ray_camvector, t_point *to)
{
	t_ray	*ray;
	double	distance;
	char 	side;

	(void) to;
	(void) ray_camvector;
	distance = -1;
	cub_update_cam_vector(data);
	ray = ft_calloc(1, sizeof(t_ray));
	if (!ray)
		cub_handle_fatal(data, NULL);
	ray->raydir = cub_init_point_double(0, 0);
	ray->current_cell = cub_init_point(0, 0);
	ray->step_cell = cub_init_point(0, 0);
	ray->delta = cub_init_point_double(0, 0);
	ray->side_dist = cub_init_point_double(0, 0);
	ray->raydir = ray_dirvector;
	ray->current_cell->x = (int) data->player_pos->xd;
	ray->current_cell->y = (int) data->player_pos->yd;
	ray->delta->xd = fabs(1 / ray->raydir->xd);
	ray->delta->yd = fabs(1 / ray->raydir->yd);
	ray->has_hit = false;
	compute_increments(ray, data->player_pos);
	if (data->debug == 'v')
		debug_ray(ray);
	while (!ray->has_hit)
	{
		if (ray->side_dist->xd < ray->side_dist->yd)
		{
			if (data->debug == 'v')
				printf("adjusting x by delta %f and moving to cell at %d \n", ray->delta->xd, ray->step_cell->x);
			ray->side_dist->xd += ray->delta->xd;
			ray->current_cell->x += ray->step_cell->x;
			side = 'x';
		}
		else
		{
			if (data->debug == 'v')	
				printf("adjusting y by delta %f and moving to cell at %d \n", ray->delta->yd, ray->step_cell->y);
			ray->side_dist->yd += ray->delta->yd;
			ray->current_cell->y += ray->step_cell->y;
			side = 'y';
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
	distance = compute_dist(data, ray, side) * data->minimap->tilesize;
	return (distance);
}

void	cub_drawLine(t_img *img, t_point *from, t_point *to)
{
	int		steps;
	t_point	delta;
	t_point	inc;
	t_point	draw;
	int		i;

	delta.xd = to->xd - from->xd;
	delta.yd = to->yd - from->yd;
	if (fabs(delta.xd) > fabs(delta.yd))
		steps = round(fabs(delta.xd));
	else
		steps = round(fabs(delta.yd));
	inc.xd = delta.xd / (double) steps;
	inc.yd = delta.yd / (double) steps;
	draw.xd = from->xd;
	draw.yd = from->yd;
	i = 0;
	while (i < steps)
	{
		cub_put_pix_to_img(img, round(draw.xd), round(draw.yd), L_RED);
		draw.xd += inc.xd;
		draw.yd += inc.yd;
		i++;
	}
}

// starting from topleftmost corner
void	cub_draw_rect(t_img *img, t_point *start, int w, int h, unsigned int color)
{
	int x;
	int	y;

	y = start->y;
	while ((double) y < start->yd + h)
	{
		x = start->x;
		while ((double) x < start->xd + w)
		{
			// printf("putting pix of color %x at x %d and y %d\n", color, x, y);
			cub_put_pix_to_img(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	cub_drawLine_angle(t_data *data, t_img *img, t_point *from, int degrees, double len)
{
	t_point	to;
	// t_point from_resized;
	double	radians;
	t_point	*ray_dirvector;
	t_point	*ray_camvector;
	double	distance;

	(void) data;
	radians = ft_to_rad(degrees);

	ray_dirvector = ft_rotate_vector_new(data->dir_vector, -radians);
	ray_camvector = ft_rotate_vector_new(data->cam_vector, -radians);
	distance = measure_dist_to_wall(data, ray_dirvector, ray_camvector, &to);
	if (distance == -1)
		distance = len;
	to.xd = from->xd + ray_dirvector->xd * distance;
	to.yd = from->yd + ray_dirvector->yd * distance;
	cub_drawLine(img, from, &to);
	free(ray_camvector);
	free(ray_dirvector);
}

void	cub_draw_cone(t_data *data, t_img *img, t_point *from, int degrees, int bisectlen)
{
	int		i;

	(void) from;
	i = -(degrees / 2);
	while (i < degrees / 2)
	{
		cub_drawLine_angle(data, img, from, i, bisectlen);
		i += 2;
	}
}

t_point	*cub_init_point(int x, int y)
{
	t_point	*point;

	point = ft_calloc(1, sizeof(t_point));
	point->x = x;
	point->y = y;
	point->xd = (float)x;
	point->yd = (float)y;
	return (point);
}

t_point	*cub_init_point_double(double x, double y)
{
	t_point	*point;

	point = ft_calloc(1, sizeof(t_point));
	point->xd = x;
	point->yd = y;
	point->x = round(x);
	point->y = round(y);
	return (point);
}