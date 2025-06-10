/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:44 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/10 15:35:07 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_bonus.h"

bool	cub_are_infos_filled(t_data *data)
{
	t_parsed_map	*map;

	map = data->parsed_map;
	return (map->has_ceiling && map->has_floor && map->paths[0] != NULL
		&& map->paths[1] != NULL && map->paths[2] != NULL
		&& map->paths[3] != NULL);
}

static void	cub_add_ceiling_or_floor_color(t_data *data, char *trimmed,
		char *line, bool *has_matched)
{
	unsigned int	color;
	char			*color_part;

	*has_matched = true;
	color_part = trimmed + 1;
	while (*color_part == ' ' || *color_part == '\t')
		color_part++;
	if (cub_parse_color(color_part, &color))
		cub_handle_fatal_parse(data, data->parsed_map->fd, line,
			MSP_INVALID_COLOR);
	if (!ft_strncmp(trimmed, "F", 1))
	{
		if (data->parsed_map->has_ceiling)
			cub_handle_fatal_parse(data, data->parsed_map->fd, line,
				"Duplicate floor color");
		data->parsed_map->floor_color = color;
		data->parsed_map->has_ceiling = true;
	}
	else
	{
		if (data->parsed_map->has_floor)
			cub_handle_fatal_parse(data, data->parsed_map->fd, line,
				"Duplicate ceiling color");
		data->parsed_map->ceiling_color = color;
		data->parsed_map->has_floor = true;
	}
}

static void	cub_init_cardinal_codes(char **codes)
{
	codes[0] = "NO";
	codes[1] = "SO";
	codes[2] = "WE";
	codes[3] = "EA";
}

static void	cub_handle_matching_code(t_data *data, int i, char *line,
		char *trimmed)
{
	char	*path_start;
	char	*path_end;
	size_t	path_len;

	if (data->parsed_map->paths[i])
		cub_handle_fatal_parse(data, data->parsed_map->fd, line,
			"Duplicate texture path");
	path_start = trimmed + 2;
	while (*path_start == ' ' || *path_start == '\t')
		path_start++;
	if (!*path_start)
		cub_handle_fatal_parse(data, data->parsed_map->fd, line,
			"Missing texture path");
	path_end = path_start;
	while (*path_end && *path_end != ' ' && *path_end != '\t')
		path_end++;
	while (*path_end == ' ' || *path_end == '\t')
		path_end++;
	if (*path_end)
		cub_handle_fatal_parse(data, data->parsed_map->fd, line,
			"Extra content after texture path");
	path_len = path_end - path_start;
	while (path_len > 0 && (path_start[path_len - 1] == ' '
			|| path_start[path_len - 1] == '\t'))
		path_len--;
	data->parsed_map->paths[i] = ft_substr(path_start, 0, path_len);
	if (!data->parsed_map->paths[i])
		cub_handle_fatal_parse(data, data->parsed_map->fd, line, MSG_ALLOC);
}

void	cub_try_add_texture_paths_and_colors(t_data *data, char *line)
{
	char	*codes[4];
	char	*trimmed;
	int		i;
	bool	has_matched;

	cub_init_cardinal_codes(codes);
	trimmed = cub_trim_full(line);
	has_matched = false;
	i = 0;
	while (i < 4)
	{
		if (!ft_strncmp(trimmed, codes[i], 2) && (trimmed[2] == ' '
				|| trimmed[2] == '\t'))
		{
			has_matched = true;
			cub_handle_matching_code(data, i, line, trimmed);
			break ;
		}
		i++;
	}
	if ((!ft_strncmp(trimmed, "F", 1) && (trimmed[1] == ' '
				|| trimmed[1] == '\t')) || (!ft_strncmp(trimmed, "C", 1)
			&& (trimmed[1] == ' ' || trimmed[1] == '\t')))
		cub_add_ceiling_or_floor_color(data, trimmed, line, &has_matched);
	if (!has_matched)
		cub_handle_fatal_parse(data, data->parsed_map->fd, line,
			MSP_INVALID_LINE);
}
