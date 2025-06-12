/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goal_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:34:24 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/11 15:53:53 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_bonus.h"

void	check_left_tex(t_data *data, t_ray *ray, int **keeper_tex)
{
	int	anim_inc;

	(void) ray;
	if (data->goal->position == GOAL_LEFT
		&& data->goal->has_catched == false)
		*keeper_tex = data->tex[LEFT_FAIL];
	else if (data->goal->position == GOAL_LEFT
		&& data->goal->has_catched == true)
		*keeper_tex = data->tex[LEFT_CATCH];
	else if (data->goal->position == GOAL_RIGHT && !data->goal->has_catched)
	{
		anim_inc = data->goal->anim_count / 10 + LEFT_PASS_1;
		*keeper_tex = data->tex[anim_inc];
	}
	else if (data->goal->win)
	{
		*keeper_tex = data->tex[EAST_HIT];
	}
}


void	check_right_tex(t_data *data, t_ray *ray, int **keeper_tex)
{
	int	anim_inc;

	(void) ray;
	if (data->goal->position == GOAL_RIGHT
		&& data->goal->has_catched == false)
		*keeper_tex = data->tex[RIGHT_FAIL];
	else if (data->goal->position == GOAL_RIGHT
		&& data->goal->has_catched == true)
		*keeper_tex = data->tex[RIGHT_CATCH];
	else if (data->goal->position == GOAL_LEFT && !data->goal->has_catched)
	{
		anim_inc = data->goal->anim_count / 10 + RIGHT_PASS_1;
		*keeper_tex = data->tex[anim_inc];
	}
	else if (data->goal->win)
	{
		*keeper_tex = data->tex[WEST_HIT];
	}
}

int	*select_keeper_tex(t_data *data, t_ray *ray)
{
	int	*keeper_tex;

	// if (data->goal->win)
	// 	keeper_tex = NULL;
	keeper_tex = NULL;
	if (ray->hit_dir == GOAL_CENTER && data->goal->position == GOAL_CENTER
		&& !data->goal->has_catched && !data->goal->win)
		keeper_tex = data->tex[CENTER_WAIT];
	else if (ray->hit_dir == GOAL_CENTER && data->goal->win)
		keeper_tex = data->tex[TROPHY];
	else if (ray->hit_dir == GOAL_LEFT)
		check_left_tex(data, ray, &keeper_tex);
	else if (ray->hit_dir == GOAL_RIGHT)
		check_right_tex(data, ray, &keeper_tex);
	else
		keeper_tex = NULL;
	return (keeper_tex);
}

int	cub_merge_goal_col(t_data *data, t_ray *ray, double pos, double texture_x)
{
	int	*keeper_tex;
	int	color;
	int	index;

	index = (int)(TEXTURE_SIZE * ((int)pos & (TEXTURE_SIZE - 1)))
		+ (int)texture_x;
	keeper_tex = select_keeper_tex(data, ray);
	if (keeper_tex && keeper_tex[index] != INVISIBLE)
		color = keeper_tex[index];
	else
		color = data->tex[ray->hit_dir][index];
	return (color);
}
