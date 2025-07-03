/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:26 by fpetit            #+#    #+#             */
/*   Updated: 2025/07/03 15:27:29 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_find_player(t_data *data, t_parsed_map *parsed_map)
{
	int	i;
	int	found;

	i = 0;
	found = 0;
	while (parsed_map->elems && parsed_map->elems[i])
	{
		if (parsed_map->elems[i] == E_NORTH || parsed_map->elems[i] == E_SOUTH
			|| parsed_map->elems[i] == E_EAST || parsed_map->elems[i] == E_WEST)
		{
			found++;
			if (found > 1)
				cub_handle_fatal(data, MSP_MPP);
			parsed_map->player_orientation = parsed_map->elems[i];
			parsed_map->player_pos = i;
			parsed_map->elems[i] = 'P';
		}
		i++;
	}
	if (found == 0)
		cub_handle_fatal(data, MSP_MIP);
}
