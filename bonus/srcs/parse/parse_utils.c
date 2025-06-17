/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:59 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/17 20:34:25 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

bool	cub_is_valid_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

int	cub_count_elements(char **split)
{
	int	count;

	count = 0;
	if (!split)
		return (0);
	while (split[count])
		count++;
	return (count);
}

void	cub_compute_adjacent_indexes_x(t_parsed_map *map, int i, int *left_i, \
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

void	cub_compute_adjacent_indexes_y(t_parsed_map *map, int i, int *up_i, \
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

void	cub_check_map_not_started(t_data *data, char *line)
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
