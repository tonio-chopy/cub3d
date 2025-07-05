/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:41:23 by fpetit            #+#    #+#             */
/*   Updated: 2025/07/03 21:03:53 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_cleanup_audio(t_data *data)
{
	if (!data->goal || !data->goal->is_soccer)
		return ;
	system("killall paplay 2>/dev/null");
	cub_stop_audio(data, true);
}

void	cub_clean_minimap(t_data *data, t_minimap *minimap)
{
	if (!minimap)
		return ;
	if (minimap->map)
		cub_clean_img(data, minimap->map);
	free(minimap);
}

void	cub_clean_goal(t_data *data, t_goal *goal)
{
	int	i;

	if (!goal)
		return ;
	if (goal->ballsprites)
	{
		i = 0;
		while (i < 5)
		{
			free(goal->ballsprites[i]);
			i++;
		}
		free(goal->ballsprites);
	}
	if (goal->ok)
		cub_clean_img(data, goal->ok);
	if (goal->ko)
		cub_clean_img(data, goal->ko);
	free(goal);
}

void	cub_clean_sprite(t_sprite *sprite)
{
	int	i;

	if (!sprite)
		return ;
	if (sprite->sprites)
	{
		i = 0;
		while (i < sprite->sprite_nb)
		{
			if (sprite->sprites[i])
				free(sprite->sprites[i]);
			i++;
		}
		free(sprite->sprites);
	}
	if (sprite->pos)
		free(sprite->pos);
	free(sprite);
}

void	cub_clean_bonus(t_data *data)
{
	if (!data)
		return ;
	cub_cleanup_audio(data);
	if (data->minimap)
		cub_clean_minimap(data, data->minimap);
	if (data->goal)
		cub_clean_goal(data, data->goal);
	if (data->balls)
		cub_clean_balls(data);
	if (data->cup)
		cub_clean_sprite(data->cup);
	if (data->zbuffer)
		free(data->zbuffer);
	if (data->sprite_distance)
		free(data->sprite_distance);
}
