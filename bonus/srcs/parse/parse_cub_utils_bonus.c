/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:27:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/07/05 12:02:41 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_update_sprite_pos(t_data *data)
{
	int				i;
	int				j;
	t_parsed_map	*map;

	map = data->parsed_map;
	i = 0;
	j = 0;
	while (map->elems[i])
	{
		if (map->elems[i] == E_BALL_VISITED)
		{
			data->balls[j]->pos = cub_get_center_coord_from_index(data, i);
			if (!data->balls[j]->pos)
				cub_handle_fatal(data, MSG_ALLOC);
			j++;
		}
		i++;
	}
}

int	count_sprites(t_parsed_map *map)
{
	int	i;
	int	nb;

	i = 0;
	nb = 0;
	while (map->elems[i])
	{
		if (map->elems[i] == E_BALL_VISITED)
			nb++;
		i++;
	}
	return (nb);
}

bool	is_only_whitespace(char *line)
{
	int	i;

	if (!line)
		return (true);
	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n'
			&& line[i] != '\r')
			return (false);
		i++;
	}
	return (true);
}
