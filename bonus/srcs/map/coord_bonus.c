/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:35:05 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/29 14:37:44 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

t_vec	*cub_get_centercoord_norm(t_parsed_map *map, int index)
{
	t_vec	*p;
	double	x;
	double	y;

	x = (index % map->width) + 0.5;
	y = (index / map->width) + 0.5;
	p = cub_init_vec_double(x, y);
	if (!p)
		return (NULL);
	return (p);
}

t_vec	*cub_get_topleftcoord_adjusted(t_parsed_map *map, t_minimap *mini, \
int index)
{
	t_vec	*p;
	double	x;
	double	y;

	x = mini->x_offset + (index % map->width) * round(mini->tilesize);
	y = mini->y_offset + (index / map->width) * round(mini->tilesize);
	p = cub_init_vec_double(x, y);
	if (!p)
		return (NULL);
	return (p);
}

t_vec	*cub_get_center_coord_from_index(t_data *data, int index)
{
	t_vec	*vec;

	vec = cub_init_vec_double(index % data->parsed_map->width, index
			/ data->parsed_map->width);
	if (!vec)
		return (NULL);
	vec->xd += 0.5;
	vec->yd += 0.5;
	return (vec);
}

t_vec	*cub_get_coord_from_index(t_data *data, int index)
{
	t_vec	*vec;

	vec = cub_init_vec(index % data->parsed_map->width, index
			/ data->parsed_map->width);
	(void) index;
	if (!vec)
		cub_handle_fatal(data, MSG_ALLOC);
	return (vec);
}
