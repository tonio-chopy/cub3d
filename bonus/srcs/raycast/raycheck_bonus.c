/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycheck_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:35:47 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/17 16:56:28 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

t_vec	*cub_get_coord_from_index(t_data *data, int index)
{
	t_vec	*vec;

	vec = cub_init_vec(index % data->parsed_map->width, index
			/ data->parsed_map->width);
	return (vec);
}
