/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_close_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:09 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/23 13:17:26 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static bool	cub_is_on_edge(t_parsed_map *map, int i)
{
	if (i % map->width == 0 || (i + 1) % map->width == 0 || i < map->width
		|| i >= map->nb_elems - map->width)
		return (true);
	return (false);
}

static bool	cub_can_check_index(char *elems, int i)
{
	if (i >= 0 && elems[i] != '1' && elems[i] != VISITED)
		return (true);
	return (false);
}

static bool	cub_is_closing(char c)
{
	if (c == E_WALL || c == E_GOAL_LEFT || c == E_GOAL_CENTER \
|| c == E_GOAL_RIGHT || c == E_BALL)
		return (true);
	return (false);
}

static bool	cub_flood_fill(t_data *data, t_parsed_map *map, char *elems, int i)
{
	int		left_i;
	int		right_i;
	int		up_i;
	int		down_i;
	bool	is_closed;

	if (i < 0 || i >= map->nb_elems)
		return (false);
	if (cub_is_closing(elems[i]))
		return (true);
	if (cub_is_on_edge(map, i))
		return (false);
	elems[i] = VISITED;
	cub_compute_adjacent_indexes_x(map, i, &left_i, &right_i);
	cub_compute_adjacent_indexes_y(map, i, &up_i, &down_i);
	is_closed = true;
	if (cub_can_check_index(elems, left_i))
		is_closed = is_closed && cub_flood_fill(data, map, elems, left_i);
	if (cub_can_check_index(elems, right_i))
		is_closed = is_closed && cub_flood_fill(data, map, elems, right_i);
	if (cub_can_check_index(elems, up_i))
		is_closed = is_closed && cub_flood_fill(data, map, elems, up_i);
	if (cub_can_check_index(elems, down_i))
		is_closed = is_closed && cub_flood_fill(data, map, elems, down_i);
	return (is_closed);
}

void	check_map_closed(t_data *data, t_parsed_map *map)
{
	char	*elems;
	int		start;

	elems = map->elems;
	start = ft_strchri(elems, 'P');
	elems[start] = '0';
	if (cub_flood_fill(data, map, elems, start) == false)
	{
		cub_handle_fatal(data, MSP_NOT_CLOSED);
	}
	if (!cub_is_surrounded_by_walls_or_empty(map,
		map->elems, start))
		cub_handle_fatal(data, MSP_PIM);
}
