/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:59 by fpetit            #+#    #+#             */
/*   Updated: 2025/05/21 17:47:02 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	cub_parse_color(char *str, unsigned int *color)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (EXIT_FAILURE);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (cub_clean2d((void **)split, 3, 0, true), 1);
	*color = (r << 16) | (g << 8) | b;
	cub_clean2d((void **)split, 3, 0b1111, true);
	return (EXIT_SUCCESS);
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
