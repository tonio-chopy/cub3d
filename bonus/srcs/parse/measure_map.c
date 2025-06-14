/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   measure_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:34 by fpetit            #+#    #+#             */
/*   Updated: 2025/05/21 17:46:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_bonus.h"

static void	cub_update_dimension(t_data *data, char **line, int *max_w)
{
	char	*trimmed;

	trimmed = cub_trim_map(*line);
	data->parsed_map->heigth++;
	if ((int) ft_strlen(trimmed) > *max_w)
		*max_w = ft_strlen(trimmed);
	free(*line);
	*line = get_next_line(data->parsed_map->fd);
}

void	cub_measure_map(t_data *data, char *filename)
{
	int		max_w;
	char	*line;

	max_w = 0;
	data->parsed_map->fd = open(filename, R_OK);
	if (data->parsed_map->fd == -1)
		cub_handle_fatal_parse(data, data->parsed_map->fd, NULL, MSP_OPEN);
	line = get_next_line(data->parsed_map->fd);
	if (!line)
		cub_handle_fatal_parse(data, data->parsed_map->fd, line, MSP_MISSING);
	while (line && !cub_is_map_line(line))
	{
		free(line);
		line = get_next_line(data->parsed_map->fd);
	}
	if (!line)
		cub_handle_fatal_parse(data, data->parsed_map->fd, line, MSP_MISSING);
	while (line && cub_is_map_line(line))
	{
		cub_update_dimension(data, &line, &max_w);
	}
	free(line);
	close(data->parsed_map->fd);
	data->parsed_map->width = max_w;
}
