/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/20 15:05:46 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	cub_move_if_possible(t_data *data, t_vec *target, t_vec *move_vector)
{
	double	dist_to_wall;
	double	dist_move;
	double	ratio;

	dist_move = ft_vector_len(move_vector);
	if (dist_move < 0.0001)
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
	if (data->rotates_left)
	{
		ft_rotate_vector(data->cam->dir, -(ROTATION_SPEED / 5));
		ft_rotate_vector(data->cam->plane, -(ROTATION_SPEED / 5));
	}
	else if (data->rotates_right)
	{
		ft_rotate_vector(data->cam->dir, (ROTATION_SPEED / 5));
		ft_rotate_vector(data->cam->plane, (ROTATION_SPEED / 5));
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
