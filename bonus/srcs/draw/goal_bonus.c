/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   goal_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:34:24 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/09 17:34:25 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	*select_keeper_tex(t_data *data, t_ray *ray)
{
	int	*keeper_tex;

	if (data->goal->win)
		keeper_tex = NULL;
	if (ray->hit_dir == GOAL_CENTER && data->goal->position == GOAL_CENTER
		&& data->goal->has_catched == false)
		keeper_tex = data->tex[CENTER_WAIT];
	else if (ray->hit_dir == GOAL_LEFT && data->goal->position == GOAL_LEFT
		&& data->goal->has_catched == false)
		keeper_tex = data->tex[LEFT_FAIL];
	else if (ray->hit_dir == GOAL_RIGHT && data->goal->position == GOAL_RIGHT
		&& data->goal->has_catched == false)
		keeper_tex = data->tex[RIGHT_FAIL];
	else if (ray->hit_dir == GOAL_LEFT && data->goal->position == GOAL_LEFT
		&& data->goal->has_catched == true)
		keeper_tex = data->tex[LEFT_CATCH];
	else if (ray->hit_dir == GOAL_RIGHT && data->goal->position == GOAL_RIGHT
		&& data->goal->has_catched == true)
		keeper_tex = data->tex[RIGHT_CATCH];
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
