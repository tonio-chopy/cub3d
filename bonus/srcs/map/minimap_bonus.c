/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:35:11 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/28 15:33:06 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	draw_map_elem(t_data *data, t_img *img, int index, char value)
{
	int		color;
	t_vec	*start;
	double	tilesize;
	t_shape	rect;

	tilesize = data->minimap->tilesize;
	if (value == ' ')
		color = INVISIBLE;
	else if (value == '1')
		color = MAP_WALL;
	else if (value == 'G' || value == 'H' || value == 'I')
		color = GREEN;
	else if (value == 'B')
		color = YELLOW;
	else
		color = MAP_EMPTY;
	start = cub_get_topleftcoord_adjusted(data->parsed_map, data->minimap, \
index);
	if (!start)
		cub_handle_fatal(data, MSG_ALLOC);
	init_shape(start, roundf(tilesize) - 1, RECTANGLE, &rect);
	rect.color = color;
	rect.heigth = roundf(tilesize) - 1;
	cub_draw_rect(img, &rect);
	free(start);
}

void	cub_draw_minimap(t_data *data)
{
	int		i;
	char	map_value;

	map_value = ' ';
	i = 0;
	while (i < data->parsed_map->nb_elems)
	{
		map_value = data->parsed_map->elems[i];
		draw_map_elem(data, data->minimap->map, i, map_value);
		i++;
	}
}

void	cub_draw_player(t_data *data)
{
	t_vec	player;

	player.xd = data->minimap->x_offset + data->player_pos->xd * \
data->minimap->tilesize;
	player.yd = data->minimap->y_offset + data->player_pos->yd * \
data->minimap->tilesize;
	cub_draw_fov(data, &player, 60, 100);
}
