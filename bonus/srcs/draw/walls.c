/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:34:30 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/15 20:20:45 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_bonus.h"

/*
 * centers vertically
 * reduces value if overflows viewport bottom or top
 */
void	adjust_y_for_viewport(t_data *data, double pro_height, t_vec *bottom, \
t_vec *top)
{
	int	vertical_center;

	vertical_center = WIN_H * data->walls->ceiling_ratio;
	top->yd = vertical_center + pro_height / 2;
	bottom->yd = vertical_center - pro_height / 2;
	if (bottom->yd < 0)
		bottom->yd = 0;
	if (top->yd > WIN_H)
		top->yd = (double) WIN_H - 1;
}

int	get_direction(char side, t_vec *dir)
{
	if (side == 'x')
	{
		if (dir->xd < 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (dir->yd < 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

void	cub_adjust_dir_for_goals(t_data *data, t_ray *ray)
{
	char	elem;

	elem = data->parsed_map->elems[ray->current_cell->y \
* data->parsed_map->width + ray->current_cell->x];
	if (elem == E_GOAL_LEFT)
		ray->hit_dir = GOAL_LEFT;
	else if (elem == E_GOAL_CENTER)
		ray->hit_dir = GOAL_CENTER;
	else if (elem == E_GOAL_RIGHT)
		ray->hit_dir = GOAL_RIGHT;
}

// void	cub_drawline_ball(t_data *data, double dist, t_ray *ray, \
// int viewport_x)
// {
// 	t_vec	bottom;
// 	t_vec	top;
// 	int	vertical_center;

// 	if (dist < 0.0001)
// 		dist = 0.0001;
// 	ray->pro_height = WIN_H / dist;
// 	ray->hit_dir = get_direction(ray->side, ray->raydir);
// 	bottom.xd = viewport_x;
// 	top.xd = viewport_x;

	
// 	vertical_center = WIN_H * data->walls->ceiling_ratio;
// 	top.yd = vertical_center + ray->pro_height / 2;
// 	bottom.yd = vertical_center - ray->pro_height / 2;
// 	if (bottom.yd < 0)
// 		bottom.yd = 0;
// 	if (top.yd > WIN_H)
// 		top.yd = (double) WIN_H - 1;
// 	cub_apply_ball(data, &bottom, top.yd, ray);
// }

/*
 * viewport_x is the current x where we cast a ray
 * projected height = wall height * projected dist / wall dist
 * start painting from other extremity when raydir doesnt match the x or y axis
 */
void	cub_drawline_wall(t_data *data, double dist, t_ray *ray, \
int viewport_x)
{
	t_vec	bottom;
	t_vec	top;

	if (dist < 0.0001)
		dist = 0.0001;
	ray->pro_height = WIN_H / dist;
	ray->hit_dir = get_direction(ray->side, ray->raydir);
	cub_adjust_dir_for_goals(data, ray);
	bottom.xd = viewport_x;
	top.xd = viewport_x;
	adjust_y_for_viewport(data, ray->pro_height, &bottom, &top);
	cub_apply_texture(data, &bottom, top.yd, ray);
}

void	cub_draw_wall_for_x(t_data *data, int x, double degrees, \
t_vec *ray_dirvector)
{
	double	distance;
	double	distorsion_corrector;

	distorsion_corrector = cosf(ft_to_rad(degrees));
	distance = cub_measure_dist_to_wall(data, ray_dirvector) * \
distorsion_corrector;
	data->zbuffer[x] = distance;
	cub_drawline_wall(data, distance, data->ray, x);
}

// void	cub_draw_ball_for_x(t_data *data, int x, double degrees, \
// t_vec *ray_dirvector)
// {
// 	double	distance;
// 	double	distorsion_corrector;

// 	distorsion_corrector = cosf(ft_to_rad(degrees));
// 	distance = cub_measure_dist_to_ball(data, ray_dirvector) * \
// distorsion_corrector;
// 	printf("ball dist %f\n", distance);
// 	if (distance != -1 && distance < data->zbuffer[x])
// 		cub_drawline_ball(data, distance, data->ray, x);
// }

void	cub_draw_walls(t_data *data)
{
	int		x;
	double	inc_degrees;
	double	degrees;
	t_vec	*ray_dirvector;
	double	cam_x_vector;

	x = 0;
	degrees = -(FOV_DEGREES / 2);
	inc_degrees = FOV_DEGREES / (double) WIN_W;
	while (x < WIN_W)
	{
		cam_x_vector = x * 2 / (double) WIN_W - 1.0;
		degrees += inc_degrees;
		ray_dirvector = ft_rotate_vector_new(data->cam->dir, \
ft_to_rad(degrees));
		cub_draw_wall_for_x(data, x, degrees, ray_dirvector);
		x++;
		free(ray_dirvector);
	}
}

void	cub_draw_ball(t_data *data)
{
	int		ball_i;
	t_vec	*ball_pos;
	t_vec	ball_dist;
	t_vec	relative_pos;
	double	invdet;
	int		x;
	int		y;
	int		texx;
	int		texy;
	// int		d;
	int		color;

	if (data->goal->has_shot || data->goal->win)
		return ;
	ball_i = ft_strchri(data->parsed_map->elems, E_BALL);
	ball_pos = cub_get_coord_from_index(data, ball_i);
	ball_pos->xd += 0.5;
	ball_pos->yd += 0.5;

	// data->sprite->worldx = ball_pos->x;
	// data->sprite->worldy = ball_pos->y;
	ball_dist.xd = ball_pos->x - data->player_pos->xd;
	ball_dist.yd = ball_pos->y - data->player_pos->yd;
	data->sprite->distance = sqrt(ball_dist.xd * ball_dist.xd + ball_dist.yd * ball_dist.yd);
	if (data->sprite->distance < 0.5)
		return ;
	double tan_half_fov = tan(30 * PI / 180.0);
	data->cam->plane->xd = data->cam->dir->yd * tan_half_fov;
	data->cam->plane->yd = data->cam->dir->xd * tan_half_fov;
	printf("plane x %d y %d\n", data->cam->plane->x, data->cam->plane->y);
	printf("dir x %d y %d\n", data->cam->dir->x, data->cam->dir->y);
	invdet = 1.0 / (data->cam->plane->xd * data->cam->dir->yd - data->cam->dir->xd * data->cam->plane->yd);
	relative_pos.xd = invdet * (data->cam->dir->yd * ball_dist.xd  - data->cam->dir->xd * ball_dist.yd);
	relative_pos.yd = invdet * (-data->cam->plane->yd * ball_dist.xd + data->cam->plane->xd * ball_dist.yd);
	printf("relative pos y %f x %f\n", relative_pos.yd, relative_pos.xd);
	if (relative_pos.yd <= 0)
		return ;
	data->sprite->screenx = (int) ((double) WIN_W / 2.0f) * (1 + relative_pos.xd / relative_pos.yd);
	printf("screen x %d\n", data->sprite->screenx);
	data->sprite->sprite_size = abs((int) (WIN_H / relative_pos.yd));
	data->sprite->startx = data->sprite->screenx - data->sprite->sprite_size / 2;
	data->sprite->endx = data->sprite->screenx + data->sprite->sprite_size / 2;
	if (data->sprite->startx >= WIN_W || data->sprite->endx < 0)
		return ;
	data->sprite->starty = (WIN_H - data->sprite->sprite_size) / 2;
	data->sprite->endy = (WIN_H + data->sprite->sprite_size) / 2;
	if (data->sprite->starty < 0)
		data->sprite->starty = 0;
	if (data->sprite->endy >= WIN_H)
		data->sprite->endy = WIN_H - 1;
	if (data->sprite->startx < 0)
		data->sprite->startx = 0;
	if (data->sprite->endx >= WIN_W)
		data->sprite->endx = WIN_W - 1;
	x = data->sprite->startx;
	printf(" x %d to %d -- y %d to %d\n", x, data->sprite->endx, data->sprite->starty, data->sprite->endy);
	while (x < data->sprite->endx)
	{
		if (data->sprite->distance < data->zbuffer[x] - 0.1f)
		{
			texx = (int) (BALL_SIZE * (x - data->sprite->startx) / (float) data->sprite->sprite_size);
			y = data->sprite->starty;
			while (y < data->sprite->endy)
			{
				texy = (int) (BALL_SIZE * (y - data->sprite->starty) / data->sprite->sprite_size);
				color = data->sprites[0][texy * BALL_SIZE + texx];
				// printf("for x %d y %d at texx %d and texy %d color is %d\n", x, y, texx, texy, color);
				if (color != INVISIBLE)
					cub_put_pix_to_img(data->walls->img, x, y, color);
				y++;
			}
		}
		x++;
	}
}