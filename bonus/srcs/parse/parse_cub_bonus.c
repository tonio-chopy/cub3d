/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:27:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/07/05 12:26:02 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static void	cub_parse_infos(t_data *data, char **line)
{
	*line = get_next_line(data->parsed_map->fd);
	if (!*line)
		cub_handle_fatal_parse(data, data->parsed_map->fd, *line, MSP_MISSING);
	while (*line && !cub_are_infos_filled(data))
	{
		cub_check_info_filled(data, *line);
		if (ft_strcmp(*line, "\n") && *cub_trim_full(*line))
			cub_try_add_texture_paths_and_colors(data, *line);
		free(*line);
		*line = get_next_line(data->parsed_map->fd);
	}
	if (!cub_are_infos_filled(data))
		cub_handle_fatal_parse(data, data->parsed_map->fd, *line, MSP_MISSING);
	while (*line && !cub_is_map_line(*line, data->is_bonus))
	{
		if (ft_strcmp(*line, "\n") && *cub_trim_full(*line))
			cub_handle_fatal_parse(data, data->parsed_map->fd, *line, MSP_IVC);
		free(*line);
		*line = get_next_line(data->parsed_map->fd);
	}
}

static void	handle_whitespace_line(t_map_state *state)
{
	if (state->map_started && !state->map_ended)
		state->map_ended = true;
}

static void	handle_map_content(t_data *data, char **line, t_map_state *state)
{
	char	*trimmed;

	trimmed = cub_trim_full(*line);
	if (cub_is_map_line(trimmed, data->is_bonus))
	{
		if (state->map_ended)
			cub_handle_fatal_parse(data, data->parsed_map->fd, *line,
				"Map content cannot continue after empty lines");
		state->map_started = true;
		cub_add_map_line(data, data->parsed_map, *line, state->y);
		state->y++;
	}
	else
	{
		if (state->map_started)
			cub_handle_fatal_parse(data, data->parsed_map->fd, *line,
				"Invalid content after map");
		else
			cub_handle_fatal_parse(data, data->parsed_map->fd, *line,
				MSP_UNK);
	}
}

static int	cub_parse_map(t_data *data, char **line)
{
	t_map_state	state;

	state.map_started = false;
	state.map_ended = false;
	state.y = 0;
	while (*line)
	{
		if (is_only_whitespace(*line))
			handle_whitespace_line(&state);
		else
			handle_map_content(data, line, &state);
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
	if (data->parsed_map->fd == -1)
		cub_handle_fatal(data, MSP_OPEN);
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
	data->nb_ball = count_sprites(data->parsed_map);
	cub_init_sprite_infos(data);
	cub_update_sprite_pos(data);
	return (EXIT_SUCCESS);
}
