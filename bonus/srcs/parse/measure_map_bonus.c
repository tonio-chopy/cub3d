/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   measure_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:34 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/19 17:49:19 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static void	cub_update_dimension(t_data *data, char **line, int *max_w, int fd)
{
	char	*trimmed;

	trimmed = cub_trim_map(*line);
	data->parsed_map->heigth++;
	if ((int) ft_strlen(trimmed) > *max_w)
		*max_w = ft_strlen(trimmed);
	free(*line);
	*line = get_next_line(fd);
}

void	cub_measure_map(t_data *data, char *filename)
{
	int		max_w;
	char	*line;
	int		fd;

	max_w = 0;
	fd = open(filename, R_OK);
	if (data->parsed_map->fd == -1)
		cub_handle_fatal_parse(data, fd, NULL, MSP_OPEN);
	line = get_next_line(fd);
	if (!line)
		cub_handle_fatal_parse(data, fd, line, MSP_MISSING);
	while (line && !cub_is_map_line(line, data->is_bonus))
	{
		free(line);
		line = get_next_line(fd);
	}
	if (!line)
		cub_handle_fatal_parse(data, fd, line, MSP_MISSING);
	while (line && cub_is_map_line(line, data->is_bonus))
	{
		cub_update_dimension(data, &line, &max_w, fd);
	}
	free(line);
	close(fd);
	data->parsed_map->width = max_w;
}
