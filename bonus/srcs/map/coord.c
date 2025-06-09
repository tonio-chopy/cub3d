/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coord.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:35:05 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/09 17:35:06 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

t_vec	*cub_get_centercoord_norm(t_parsed_map *map, t_minimap *mini, int index)
{
	t_vec	*p;
	double	x;
	double	y;

	(void) mini;
	x = (index % map->width) + 0.5;
	y = (index / map->width) + 0.5;
	p = cub_init_vec_double(x, y);
	return (p);
}

t_vec	*cub_get_topleftcoord_adjusted(t_parsed_map *map, t_minimap *mini, \
int index)
{
	t_vec	*p;
	double	x;
	double	y;

	x = mini->x_offset + (index % map->width) * roundf(mini->tilesize);
	y = mini->y_offset + (index / map->width) * roundf(mini->tilesize);
	p = cub_init_vec_double(x, y);
	return (p);
}
