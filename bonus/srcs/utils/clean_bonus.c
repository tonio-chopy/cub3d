/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:41:23 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/27 21:11:07 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_cleanup_audio(t_data *data)
{
	cub_stop_song(data, true);
}

void	cub_clean_minimap(t_data *data, t_minimap *minimap)
{
	if (!minimap)
		return ;
	if (minimap->map)
		cub_clean_img(data, minimap->map);
	free(minimap);
}

void	cub_clean_goal(t_goal *goal)
{
	if (!goal)
		return ;
	free(goal);
}

void	cub_clean_sprite(t_sprite *sprite)
{
	int	i;

	if (!sprite)
		return ;
	i = 0;
	while (i < sprite->sprite_nb)
	{
		free(sprite->sprites[i]);
		i++;
	}
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
		cub_clean_goal(data->goal);
	if (data->ball)
		cub_clean_sprite(data->ball);
	if (data->cup)
		cub_clean_sprite(data->cup);
	if (data->zbuffer)
		free(data->zbuffer);
}
