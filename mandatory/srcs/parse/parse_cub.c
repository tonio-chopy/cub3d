/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:27:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/05/21 17:40:09 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static void	cub_parse_infos(t_data *data, char **line)
{
	*line = get_next_line(data->parsed_map->fd);
	if (!*line)
		cub_handle_fatal_parse(data, data->parsed_map->fd, *line, \
MSP_MISSING);
	while (*line && !cub_are_infos_filled(data))
	{
		cub_check_map_not_started(data, *line);
		if (ft_strcmp(*line, "\n"))
			cub_try_add_texture_paths_and_colors(data, *line);
		free(*line);
		*line = get_next_line(data->parsed_map->fd);
	}
}

static int	cub_parse_map(t_data *data, char **line)
{
	char	*trimmed;
	int		y;

	while (*line && !ft_strcmp(*line, "\n"))
	{
		free(*line);
		*line = get_next_line(data->parsed_map->fd);
	}
	y = 0;
	while (*line)
	{
		trimmed = cub_trim_full(*line);
		if (!trimmed)
			cub_handle_fatal_parse(data, data->parsed_map->fd, *line, MSP_ELM);
		else if (cub_is_map_line(trimmed))
			cub_add_map_line(data, data->parsed_map, *line, y);
		else
			cub_handle_fatal_parse(data, data->parsed_map->fd, *line, MSP_UNK);
		free(*line);
		*line = get_next_line(data->parsed_map->fd);
		y++;
	}
	free(*line);
	return (EXIT_SUCCESS);
}

int	cub_parse_file(char *filename, t_data *data)
{
	char	*line;

	line = NULL;
	cub_check_file(data, filename);
	cub_measure_map(data, filename);
	data->parsed_map->fd = open(filename, R_OK);
	data->parsed_map->elems = ft_calloc(data->parsed_map->heigth * \
data->parsed_map->width + 1, sizeof(char));
	data->parsed_map->nb_elems = data->parsed_map->heigth * \
data->parsed_map->width;
	if (!data->parsed_map->elems)
		cub_handle_fatal_parse(data, data->parsed_map->fd, NULL, MSG_ALLOC);
	cub_parse_infos(data, &line);
	cub_parse_map(data, &line);
	close(data->parsed_map->fd);
	cub_find_player(data, data->parsed_map);
	check_map_closed(data, data->parsed_map);
	data->parsed_map->elems[data->parsed_map->player_pos] = '0';
	return (EXIT_SUCCESS);
}
