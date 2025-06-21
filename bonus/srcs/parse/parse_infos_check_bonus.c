/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos_check_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 07:52:15 by tonio-chopy       #+#    #+#             */
/*   Updated: 2025/06/21 18:00:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

bool	cub_are_infos_filled(t_data *data)
{
	t_parsed_map	*map;

	map = data->parsed_map;
	return (map->has_ceiling && map->has_floor && map->paths[0] != NULL
		&& map->paths[1] != NULL && map->paths[2] != NULL
		&& map->paths[3] != NULL);
}

void	cub_init_cardinal_codes(char **codes)
{
	codes[0] = "NO";
	codes[1] = "SO";
	codes[2] = "WE";
	codes[3] = "EA";
}

void	cub_set_ceiling_color(t_data *data, char *line,
		unsigned int color)
{
	if (data->parsed_map->has_ceiling)
		cub_handle_fatal_parse(data, data->parsed_map->fd, line,
			MSP_DCC);
	data->parsed_map->ceiling_color = color;
	data->parsed_map->has_ceiling = true;
}

void	cub_set_floor_color(t_data *data, char *line, unsigned int color)
{
	if (data->parsed_map->has_floor)
		cub_handle_fatal_parse(data, data->parsed_map->fd, line,
		MSP_DFC);
	data->parsed_map->floor_color = color;
	data->parsed_map->has_floor = true;
}
