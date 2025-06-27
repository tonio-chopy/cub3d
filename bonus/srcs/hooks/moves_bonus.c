/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:34:48 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/27 20:58:31 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_move_if_possible(t_data *data, t_vec *target, t_vec *move_vector)
{
	double	ratio;
	double	dist_to_wall;
	double	dist_move;
	// t_vec	direction;
	dist_move = ft_vector_len(move_vector);
	if (dist_move < 0.0000001)
		return ;
	ft_normalize_vector(move_vector);
	dist_to_wall = cub_measure_dist_to_wall(data, move_vector);
	if (dist_move + MOVEMENT_SECURITY < dist_to_wall)
	{
		data->player_pos->xd = target->xd;
		data->player_pos->yd = target->yd;
	}
	else
	{
		ratio = (dist_to_wall - MOVEMENT_SECURITY) / dist_move;
		data->player_pos->xd += (target->xd - data->player_pos->xd) * ratio;
		data->player_pos->yd += (target->yd - data->player_pos->yd) * ratio;
	}
}

void	cub_update_rotation(t_data *data)
{
	double	old_dir_x;
	double	old_plane_x;
	double	remain_deg;
	double	speed_deg;

	old_dir_x = data->cam->dir->xd;
	old_plane_x = data->cam->plane->xd;
	speed_deg = ft_to_deg(ROTATION_SPEED);
	if (data->rotates_left)
	{
// 		data->cam->dir->xd = data->cam->dir->xd * cos(ROTATION_SPEED)
		// 		- data->cam->dir->yd * sin(ROTATION_SPEED);
// 		data->cam->dir->yd = old_dir_x * sin(ROTATION_SPEED)
		// 		+ data->cam->dir->yd * cos(ROTATION_SPEED);
// 		data->cam->plane->xd = data->cam->plane->xd * cos(ROTATION_SPEED)
		// 		- data->cam->plane->yd * sin(ROTATION_SPEED);
// 		data->cam->plane->yd = old_plane_x * sin(ROTATION_SPEED)
		// 		+ data->cam->plane->yd * cos(ROTATION_SPEED);
		ft_rotate_vector(data->cam->dir, -(ROTATION_SPEED));
		cub_update_plane_vector(data);
		// ft_rotate_vector(data->cam->plane, -(ROTATION_SPEED));
		// data->cam->plane->xd = -data->cam->dir->yd;
		// data->cam->plane->yd = data->cam->dir->xd;
		data->rotates_left = false;
		if (data->cam->angle - speed_deg >= 0)
			data->cam->angle -= speed_deg;
		else
		{
			remain_deg = data->cam->angle - ft_to_deg(ROTATION_SPEED);
			data->cam->angle = 360 + remain_deg;
		}
	}
	else if (data->rotates_right)
	{
// 		data->cam->dir->xd = data->cam->dir->xd * cos(-ROTATION_SPEED)
		// 		- data->cam->dir->yd * sin(-ROTATION_SPEED);
// 		data->cam->dir->yd = old_dir_x * sin(-ROTATION_SPEED)
		// 		+ data->cam->dir->yd * cos(-ROTATION_SPEED);
// 		data->cam->plane->xd = data->cam->plane->xd * cos(-ROTATION_SPEED)
		// 		- data->cam->plane->yd * sin(-ROTATION_SPEED);
// 		data->cam->plane->yd = old_plane_x * sin(-ROTATION_SPEED)
		// 		+ data->cam->plane->yd * cos(-ROTATION_SPEED);
		ft_rotate_vector(data->cam->dir, (ROTATION_SPEED));
		cub_update_plane_vector(data);
		// ft_rotate_vector(data->cam->plane, (ROTATION_SPEED));
		// data->cam->plane->xd = -data->cam->dir->yd;
		// data->cam->plane->yd = data->cam->dir->xd;
		data->rotates_right = false;
		if (data->cam->angle + speed_deg <= 360)
			data->cam->angle += speed_deg;
		else
			data->cam->angle = data->cam->angle + speed_deg - 360;
	}
}

void	cub_update_lr(t_data *data, t_vec *move_vector)
{
	if (data->move_left)
	{
		move_vector->xd += (data->cam->dir->yd * MOVEMENT_SPEED);
		move_vector->yd += (-data->cam->dir->xd * MOVEMENT_SPEED);
	}
	else if (data->move_right)
	{
		move_vector->xd += (-data->cam->dir->yd * MOVEMENT_SPEED);
		move_vector->yd += (data->cam->dir->xd * MOVEMENT_SPEED);
	}
}

void	cub_update_translation(t_data *data)
{
	t_vec	target;
	t_vec	move_vector;

	target.xd = data->player_pos->xd;
	target.yd = data->player_pos->yd;
	move_vector.xd = 0;
	move_vector.yd = 0;
	if (data->move_forward)
	{
		move_vector.xd += (data->cam->dir->xd * MOVEMENT_SPEED);
		move_vector.yd += (data->cam->dir->yd * MOVEMENT_SPEED);
	}
	else if (data->move_backward)
	{
		move_vector.xd -= (data->cam->dir->xd * MOVEMENT_SPEED);
		move_vector.yd -= (data->cam->dir->yd * MOVEMENT_SPEED);
	}
	cub_update_lr(data, &move_vector);
	target.xd += move_vector.xd;
	target.yd += move_vector.yd;
	cub_move_if_possible(data, &target, &move_vector);
}
