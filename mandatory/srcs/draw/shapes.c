/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/28 15:28:17 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	cub_draw_ceiling_and_floor(t_data *data)
{
	t_vec	*coord;
	t_shape	rect;

	coord = cub_init_vec_double(0, 0);
	if (!coord)
		cub_handle_fatal(data, MSG_ALLOC);
	init_shape(coord, WIN_W, RECTANGLE, &rect);
	rect.heigth = (double) WIN_H * data->walls->ceiling_ratio;
	rect.color = data->parsed_map->ceiling_color;
	cub_draw_rect(data->walls->img, &rect);
	rect.start->yd = rect.heigth;
	rect.heigth = (double) WIN_H - rect.heigth;
	rect.color = data->parsed_map->floor_color;
	cub_draw_rect(data->walls->img, &rect);
	free(coord);
}
