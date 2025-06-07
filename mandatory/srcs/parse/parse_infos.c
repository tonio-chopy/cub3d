/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:44 by fpetit            #+#    #+#             */
/*   Updated: 2025/05/21 17:46:49 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

bool	cub_are_infos_filled(t_data *data)
{
	t_parsed_map	*map;

	map = data->parsed_map;
	return (map->has_ceiling && map->has_floor \
&& map->paths[0] != NULL \
&& map->paths[1] != NULL \
&& map->paths[2] != NULL \
&& map->paths[3] != NULL \
);
}

static void	cub_add_ceiling_or_floor_color(t_data *data, char *trimmed, \
char *line, bool *has_matched)
{
	unsigned int	color;

	*has_matched = true;
	if (cub_parse_color(trimmed + 2, &color))
		cub_handle_fatal_parse(data, data->parsed_map->fd, line, \
MSP_INVALID_COLOR);
	if (!ft_strncmp(trimmed, "F ", 2))
	{
		data->parsed_map->ceiling_color = color;
		data->parsed_map->has_ceiling = true;
	}
	else
	{
		data->parsed_map->floor_color = color;
		data->parsed_map->has_floor = true;
	}
}

static void	cub_init_cardinal_codes(char **codes)
{
	codes[0] = "NO ";
	codes[1] = "SO ";
	codes[2] = "WE ";
	codes[3] = "EA ";
}

static void	cub_handle_matching_code(t_data *data, int i, char *line, \
char *trimmed)
{
	data->parsed_map->paths[i] = ft_strdup(trimmed + 3);
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
		if (!ft_strncmp(trimmed, codes[i], 3))
		{
			has_matched = true;
			cub_handle_matching_code(data, i, line, trimmed);
			break ;
		}
		i++;
	}
	if (!ft_strncmp(trimmed, "F ", 2) || !ft_strncmp(trimmed, "C ", 2))
		cub_add_ceiling_or_floor_color(data, trimmed, line, &has_matched);
	if (!has_matched)
		cub_handle_fatal_parse(data, data->parsed_map->fd, line, \
MSP_INVALID_LINE);
}
