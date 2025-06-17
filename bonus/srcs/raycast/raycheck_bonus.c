/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycheck_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:35:47 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/17 18:22:43 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	get_direction(char side, t_vec *dir)
{
	if (side == 'x')
	{
		if (dir->xd < 0)
			return (EAST);
		else
			return (WEST);
	}
	else
	{
		if (dir->yd < 0)
			return (SOUTH);
		else
			return (NORTH);
	}
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
	if (!vec)
		return (NULL);
	return (vec);
}
