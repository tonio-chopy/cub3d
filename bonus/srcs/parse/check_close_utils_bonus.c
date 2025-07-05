/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_close_utils_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 10:44:25 by alaualik          #+#    #+#             */
/*   Updated: 2025/07/05 10:51:05 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static bool	cub_is_ball_surrounded(t_parsed_map *map, int i)
{
	int		left_i;
	int		right_i;
	int		up_i;
	int		down_i;

	if (cub_is_on_edge(map, i))
		return (false);
	cub_compute_adjacent_indexes_x(map, i, &left_i, &right_i);
	cub_compute_adjacent_indexes_y(map, i, &up_i, &down_i);
	if (left_i >= 0 && map->elems[left_i] == E_EMPTY)
		return (false);
	if (right_i >= 0 && map->elems[right_i] == E_EMPTY)
		return (false);
	if (up_i >= 0 && map->elems[up_i] == E_EMPTY)
		return (false);
	if (down_i >= 0 && map->elems[down_i] == E_EMPTY)
		return (false);
	return (true);
}

void	cub_check_balls_validity(t_data *data, t_parsed_map *map)
{
	int	i;

	i = 0;
	while (i < map->nb_elems)
	{
		if (map->elems[i] == E_BALL)
		{
			if (!cub_is_ball_surrounded(map, i))
				cub_handle_fatal(data, "Error\nball too close to map border");
		}
		i++;
	}
}
