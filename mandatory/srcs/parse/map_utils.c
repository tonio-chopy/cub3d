/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 07:07:00 by tonio-chopy       #+#    #+#             */
/*   Updated: 2025/06/20 18:20:56 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	cub_compute_adjacent_indexes_x(t_parsed_map *map, int i, int *left_i,
		int *right_i)
{
	if (i % map->width != 0)
		*left_i = i - 1;
	else
		*left_i = -1;
	if ((i + 1) % map->width < map->width)
		*right_i = i + 1;
	else
		*right_i = -1;
}

void	cub_compute_adjacent_indexes_y(t_parsed_map *map, int i, int *up_i,
		int *down_i)
{
	if (i > map->width)
		*up_i = i - map->width;
	else
		*up_i = -1;
	if (i + map->width < map->nb_elems)
		*down_i = i + map->width;
	else
		*down_i = -1;
}

void	cub_check_info_filled(t_data *data, char *line)
{
	if (cub_is_map_line(line))
	{
		if (!cub_are_infos_filled(data))
		{
			free(line);
			close(data->parsed_map->fd);
			cub_handle_fatal(data, MSP_MISSING);
		}
	}
}
