/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:34:31 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/15 13:44:08 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_bonus.h"

void	cub_transform_pos(t_data *data, t_vec *ball_pos)
{
	double	inverseDeterminant;
	t_vec	*dir;
	t_vec	*plane;
	double	tr_x;
	double	tr_y;

	dir = data->cam->dir;
	plane = data->cam->plane;
	inverseDeterminant = 1.0 / (data->cam->plane->xd * data->cam->dir->yd \
- data->cam->dir->xd * data->cam->plane->yd);
	tr_x = inverseDeterminant * (dir->yd * ball_pos->xd - dir->xd * ball_pos->yd);
	tr_y = inverseDeterminant * (- plane->yd * ball_pos->xd - plane->xd * ball_pos->yd);
	ball_pos->xd = tr_x;
	ball_pos->yd = tr_y;
}

// t_vec	*get_start(int height, int width, int sprite_x)
// {
// 	t_vec *start;

// 	start = cub_init_vec(0, 0);
// 	start->x = -width / 2 + sprite_x;
// 	start->y = -height / 2 + WIN_H / 2;
// 	return (start);
// }

// t_vec	*get_end(int height, int width, int sprite_x)
// {
// 	t_vec	*end;

// 	end = cub_init_vec(0, 0);
// 	end->x = width / 2 + sprite_x;
// 	end->y = height / 2 + WIN_H / 2;
// 	return (end);
// }

// void	cub_draw_vline(t_data *data, t_vec *start, t_vec *end, int texx)
// {
// 	int	y;
// 	int	pos;
// 	int	texy;
// 	int	sprite_index;
// 	int	color;

// 	y = start->y;
// 	if (y < 0)
// 		y = 0;
// 	while (y < end->y)
// 	{
		// pos = y * 256 - WIN_H * 128 + data->ball_h * 128;
		// texy = pos * BALL_SIZE / data->ball_h / 256;
		// sprite_index = data->goal->ball_anim_count / 5;
		// color = data->sprites[sprite_index][BALL_SIZE * texy + texx];
		// if (color != INVISIBLE)
		// 	cub_put_pix_to_img(data->walls->img, (int) start->x, (int) y, color);
		// y++;
// 	}
// }

// void	cub_draw_stripes(t_data *data)
// {
// 	int	sprite_x;
// 	t_vec	*start;
// 	t_vec	*end;
// 	int	x;
// 	int	texx;

// 	sprite_x = (int) (WIN_W / 2) * (1 + data->ball_pos->xd / data->ball_pos->yd);
// 	data->ball_h = abs((int)(WIN_H / data->ball_pos->yd));
// 	data->ball_w = abs((int) (WIN_H / data->ball_pos->yd));
// 	start = get_start(data->ball_h, data->ball_w, sprite_x);
// 	end = get_end(data->ball_h, data->ball_w, sprite_x);
// 	x = start->x;
// 	if (x < 0)
// 		x = 0;
// 	while (x < end->x)
// 	{
// 		texx = (int) (256 * (x - (-data->ball_w / 2 + sprite_x)) * BALL_SIZE / data->ball_w) / 256;
// 		if (data->ball_pos->yd > 0 && x > 0 && x < WIN_H && data->ball_pos->yd < data->zbuffer[x])
// 		{
// 			cub_draw_vline(data, start, end, texx);
// 		}
// 		x++;
// 	}
// }

// void	cub_draw_ball(t_data *data)
// {
// 	// double	dist_x;
// 	// double	dist_y;
// 	int		ball_i;

	// ball_i = ft_strchri(data->parsed_map->elems, E_BALL);
	// data->ball_pos = cub_get_centercoord_norm(data->parsed_map, ball_i);
	// data->ball_pos->xd = data->ball_pos->xd - data->cam->orig->xd;
	// data->ball_pos->yd = data->ball_pos->yd - data->cam->orig->yd;
	// cub_transform_pos(data, data->ball_pos);
// 	cub_draw_stripes(data);
// }


int	cub_get_ball_col(t_data *data, double pos, double texx, double texy)
{
	int	sprite_index;
	int	index;
	
	(void) pos;
	// int texture_y = ((int)pos) & (BALL_SIZE - 1);
	// int tex_x = ((int)texx) & (BALL_SIZE - 1);
	index = texy * BALL_SIZE + texx;
	sprite_index = data->goal->ball_anim_count / 10;
	if (sprite_index >= 0 && sprite_index < 5 && 
		index >= 0 && index < BALL_SIZE * BALL_SIZE)
		return (data->sprites[sprite_index][index]);
	return (INVISIBLE);
}


// void	cub_apply_ball(t_data *data, t_vec *from, double toY, t_ray *ray)
// {
// 	double			step;
// 	double			pos;
// 	unsigned int	color;
// 	double			y;
// 	// int				texy;
// 	double			texture_x;
// 	int				sprite_index;
// 	// int				ball_i;

// 	texture_x = (int) ray->wall_ratio * (BALL_SIZE - 1);
// 	y = from->yd;
// 	// ball_i = ft_strchri(data->parsed_map->elems, E_BALL);
// 	// data->ball_pos = cub_get_centercoord_norm(data->parsed_map, ball_i);
// 	// data->ball_pos->xd = data->ball_pos->xd - data->cam->orig->xd;
// 	// data->ball_pos->yd = data->ball_pos->yd - data->cam->orig->yd;
// 	// cub_transform_pos(data, data->ball_pos);
// 	// data->ball_h = abs((int)(WIN_H / data->ball_pos->yd));
// 	// data->ball_w = abs((int) (WIN_H / data->ball_pos->yd));
// 	sprite_index = 0;
// 	//  data->goal->ball_anim_count / 10;
// 	step = (double) BALL_SIZE / ray->pro_height;
// 	pos = (y - WIN_H / 2 + ray->pro_height / 2) * step;
// 	while (y < toY)
// 	{
// 		// texy = pos * BALL_SIZE / data->ball_h;
// 		color = cub_get_ball_col(data,pos, texture_x);
// 		if (color != INVISIBLE)
// 			cub_put_pix_to_img(data->walls->img, (int) from->xd, (int) y, color);
// 		y++;
// 		// color = cub_get_ball_col(data, ray, pos, texture_x);
// 		// pos += step;
// 		// if (color != INVISIBLE)
// 		// {
// 		// 	if (ray->hit_dir == NORTH || ray->hit_dir == SOUTH)
// 		// 		color = (color >> 1) & 0x7F7F7F;
// 		// 	cub_put_pix_to_img(data->walls->img, (int) from->xd, (int) y, color);
// 		// }
// 		// y++;
// 	}
// }

double	compute_dist_sprite(t_data *data, t_ray *ray, char side)
{
	double	dist;

	if (side == 'x')
	{
		dist = ((double)ray->current_cell->x - data->player_pos->xd + (1
					- ray->step_cell->x) / 2) / ray->raydir->xd;
		ray->wall_ratio = data->player_pos->yd + dist * ray->raydir->yd;
	}
	else
		dist = -1;
	// else
	// {
	// 	dist = ((double)ray->current_cell->y - data->player_pos->yd + (1
	// 				- ray->step_cell->y) / 2) / ray->raydir->yd;
	// 	ray->wall_ratio = data->player_pos->xd + dist * ray->raydir->xd;
	// }
	ray->wall_ratio -= floor(ray->wall_ratio);
	return (dist);
}

double	cub_measure_dist_to_sprite(t_data *data, t_vec *ray_dirvector)
{
	double	distance;
	int		ball_i;

	ball_i = ft_strchri(data->parsed_map->elems, E_BALL);
	distance = -1;
	reinit_ray(data, ray_dirvector);
	// data->ray->check_cell = cub_get_coord_from_index(data,
	// 	ball_i);
	compute_increments(data->ray, data->player_pos);
	cub_iter_ray(data, data->ray, BALL);
	distance = compute_dist_sprite(data, data->ray, data->ray->side);
	return (distance);
}