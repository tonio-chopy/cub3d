/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 19:35:28 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/23 17:53:27 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	cub_refresh_bonus(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	printf("current song index %d\n", data->goal->current_song);
	cub_clear_img(data->minimap->map);
	cub_draw_minimap(data);
	cub_draw_player(data);
	cub_draw_ball(data);
	cub_draw_cup(data);
	cub_draw_flags(data);
	cub_cpy_with_transparency(data->walls->img, data->minimap->map, \
data->minimap->map->location->x, data->minimap->map->location->y);
	if (data->show_help)
		cub_draw_help(data);
	return (EXIT_SUCCESS);
}
