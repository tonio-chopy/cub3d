/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:26 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/20 14:59:37 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static bool	cub_is_surrounded_by_walls_or_empty(t_parsed_map *map, char *elems,
		int i)
{
	if (i == 0 || i <= map->width)
		return (false);
	if (i > map->nb_elems - 1 - map->width)
		return (false);
	if (i % map->width != 0 && (i + 1) % map->width != 0)
	{
		if (elems[i - 1] != E_WALL && elems[i - 1] != E_INSIDE)
			return (false);
		if (elems[i + 1] != E_WALL && elems[i + 1] != E_INSIDE)
			return (false);
	}
	if (elems[i - map->width - 1] != E_WALL && elems[i - map->width
			- 1] != E_INSIDE)
		return (false);
	if (elems[i + map->width] != E_WALL && elems[i + map->width] != E_INSIDE)
		return (false);
	return (true);
}

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
			if (found++)
				cub_handle_fatal(data, "Multiple player positions!");
			if (!cub_is_surrounded_by_walls_or_empty(parsed_map,
					parsed_map->elems, i))
				cub_handle_fatal(data, "Player must be inside the map");
			parsed_map->player_orientation = parsed_map->elems[i];
			parsed_map->player_pos = i;
			parsed_map->elems[i] = 'P';
		}
		i++;
	}
	if (!found)
		cub_handle_fatal(data, "No player position found!\n");
}
