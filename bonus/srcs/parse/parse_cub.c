/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:27:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/10 15:34:53 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_bonus.h"

static void	cub_parse_infos(t_data *data, char **line)
{
	*line = get_next_line(data->parsed_map->fd);
	if (!*line)
		cub_handle_fatal_parse(data, data->parsed_map->fd, *line, MSP_MISSING);
	while (*line && !cub_are_infos_filled(data))
	{
		cub_check_map_not_started(data, *line);
		if (ft_strcmp(*line, "\n") && *cub_trim_full(*line))
			cub_try_add_texture_paths_and_colors(data, *line);
		free(*line);
		*line = get_next_line(data->parsed_map->fd);
	}
	while (*line && !cub_is_map_line(*line))
	{
		if (ft_strcmp(*line, "\n") && *cub_trim_full(*line))
			cub_handle_fatal_parse(data, data->parsed_map->fd, *line,
				"Invalid content after configuration");
		free(*line);
		*line = get_next_line(data->parsed_map->fd);
	}
}

static bool	is_only_whitespace(char *line)
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

static int	cub_parse_map(t_data *data, char **line)
{
	char	*trimmed;
	int		y;
	bool	map_started;
	bool	map_ended;

	map_started = false;
	map_ended = false;
	y = 0;
	while (*line)
	{
		if (is_only_whitespace(*line))
		{
			if (map_started && !map_ended)
				map_ended = true;
		}
		else
		{
			trimmed = cub_trim_full(*line);
			if (cub_is_map_line(trimmed))
			{
				if (map_ended)
					cub_handle_fatal_parse(data, data->parsed_map->fd, *line,
						"Map content cannot continue after empty lines");
				map_started = true;
				cub_add_map_line(data, data->parsed_map, *line, y);
				y++;
			}
			else
			{
				if (map_started)
					cub_handle_fatal_parse(data, data->parsed_map->fd, *line,
						"Invalid content after map");
				else
					cub_handle_fatal_parse(data, data->parsed_map->fd, *line,
						MSP_UNK);
			}
		}
		free(*line);
		*line = get_next_line(data->parsed_map->fd);
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
	data->parsed_map->elems = ft_calloc(data->parsed_map->heigth
			* data->parsed_map->width + 1, sizeof(char));
	data->parsed_map->nb_elems = data->parsed_map->heigth
		* data->parsed_map->width;
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
