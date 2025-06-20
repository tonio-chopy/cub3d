/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:41:23 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/20 19:20:53 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_cleanup_audio(void)
{
	system("pkill -f 'paplay ./sound.wav'");
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

void	cub_clean_sprites(t_data *data)
{
	int	i;

	if (!data->sprites)
		return ;
	i = 0;
	while (i < 5)
	{
		free(data->sprites[i]);
		i++;
	}
	free(data->sprites);
}

void	cub_clean_bonus(t_data *data)
{	
	// cub_cleanup_audio();
	cub_clean_minimap(data, data->minimap);
	cub_clean_goal(data->goal);
	cub_clean_sprites(data);
	if (data->sprite)
		free(data->sprite);
	if (data->zbuffer)
		free(data->zbuffer);
}