/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:27:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/05/21 15:42:59 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static char	*cub_trim_map(char *line)
{
	char	*end;
	char	*str;

	str = line;
	while (*str == '\t')
		str++;
	end = str + ft_strlen(str) - 1;
	while (end > str && (*end == '\t' || *end == '\n'))
	{
		*end-- = 0;
	}
	return (str);
}

static char	*cub_trim_full(char *line)
{
	char	*end;
	char	*str;

	str = line;
	while (*str == ' ' || *str == '\t')
		str++;
	end = str + ft_strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
	{
		*end-- = 0;
	}
	return (str);
}

static int	cub_parse_color(char *str, unsigned int *color)
{
	char	**split;

	int r, g, b;
	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (1);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (cub_clean2d((void **)split, 3, 0, true), 1);
	*color = (r << 16) | (g << 8) | b;
	cub_clean2d((void **)split, 3, 0b1111, true);
	return (0);
}

static bool	cub_is_map_line(char *line)
{
	char	*trimmed;

	trimmed = cub_trim_full(line);
	while (*trimmed == ' ' || *trimmed == '\t')
		trimmed++;
	if (*trimmed == 0)
		return (false);
	while (*trimmed)
	{
		if (*trimmed != E_WALL && *trimmed != E_INSIDE && *trimmed != E_NORTH
			&& *trimmed != E_SOUTH && *trimmed != E_EAST && *trimmed != E_WEST
			&& *trimmed != E_EMPTY)
			return (false);
		trimmed++;
	}
	return (true);
}

void	cub_cpy_elems(t_data *data, char *new, char *line)
{
	int	i;
	int	j;

	i = 0;
	while (new[i])
		i++;
	j = 0;
	while (j < data->parsed_map->width)
	{
		if (line[j])
			new[i + j] = line[j];
		else
			new[i + j] = ' ';
		j++;
	}
}

static void	cub_add_map_line(t_data *data, t_parsed_map *parsed_map, char *line)
{
	int		len;
	char	*new;
	char	*cleaned;

	cleaned = cub_trim_map(line);
	len = ft_strlen(cleaned);
	new = ft_calloc(parsed_map->nb_elems + data->parsed_map->width + 1, sizeof(char));
	if (!new)
		cub_handle_fatal_parse(data, data->parsed_map->fd, line, MSG_ALLOC);
	if (parsed_map->elems)
		ft_memcpy(new, parsed_map->elems, parsed_map->nb_elems);
	cub_cpy_elems(data, new, cleaned);
	free(parsed_map->elems);
	parsed_map->elems = new;
	parsed_map->nb_elems += data->parsed_map->width;
}

void	debug_elems(t_parsed_map *map, char *elems)
{
	int y;

	y = 0;
	while (elems && y < map->heigth)
	{
		write(1, elems, map->width);
		printf("\n");
		elems+=map->width;
		y++;
	}
}

static void	cub_find_player(t_parsed_map *parsed_map)
{
	int		i;
	int		found;

	i = 0;
	found = 0;
	debug_elems(parsed_map, parsed_map->elems);
	while (parsed_map->elems && parsed_map->elems[i])
	{
		if (parsed_map->elems[i] == E_NORTH || parsed_map->elems[i] == E_SOUTH
			|| parsed_map->elems[i] == E_EAST || parsed_map->elems[i] == E_WEST)
		{
			if (found++)
				cub_parse_error(NULL, "Multiple player positions!\n");
			parsed_map->player_orientation = parsed_map->elems[i];
			parsed_map->player_pos = i;
			parsed_map->elems[i] = 'P';
		}
		i++;
	}
	if (!found)
		cub_parse_error(NULL, "No player position found!\n");
}

void	cub_compute_adjacent_indexes_x(t_parsed_map *map, int i, int *left_i, int *right_i)
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

void	cub_compute_adjacent_indexes_y(t_parsed_map *map, int i, int *up_i, int *down_i)
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

bool	cub_is_on_edge(t_parsed_map *map, int i)
{
	if (i % map->width == 0 || (i + 1) % map->width == 0\
|| i < map->width || i >= map->nb_elems - map->width)
		return (true);
	return (false);
}

bool	cub_can_check_index(char *elems, int i)
{
	if (i >= 0 && elems[i] != '1' && elems[i] != VISITED)
		return (true);
	return (false);
}

bool	cub_flood_fill(t_parsed_map *map, char *elems, int i)
{
	int		left_i;
	int		right_i;
	int		up_i;
	int		down_i;
	bool	is_closed;

	if (i < 0 || i >= map->nb_elems)
		return (false);
	if (elems[i] == E_WALL || elems[i] == VISITED)
		return (true);
	if (cub_is_on_edge(map, i))
		return (false);
	elems[i] = VISITED;
	cub_compute_adjacent_indexes_x(map, i, &left_i, &right_i);
	cub_compute_adjacent_indexes_y(map, i, &up_i, &down_i);
	is_closed = true;
	if (cub_can_check_index(elems, left_i))
		is_closed = is_closed && cub_flood_fill(map, elems, left_i);
	if (cub_can_check_index(elems, right_i))
		is_closed = is_closed && cub_flood_fill(map, elems, right_i);
	if (cub_can_check_index(elems, up_i))
		is_closed = is_closed && cub_flood_fill(map, elems, up_i);
	if (cub_can_check_index(elems, down_i))
		is_closed = is_closed && cub_flood_fill(map, elems, down_i);
	return (is_closed);
}


void	check_map_closed(t_data *data, t_parsed_map *map)
{
	char	*elems;
	int		start;

	elems = ft_strdup(map->elems);
	if (!elems)
		cub_handle_fatal(data, MSG_ALLOC);
	start = ft_strchri(elems, 'P');
	elems[start] = '0';
	if (cub_flood_fill(map, elems, start) == false)
	{
		debug_elems(map, elems);
		free(elems);
		cub_handle_fatal(data, MSG_PARSE_NOT_CLOSED);
	}
	free(elems);
}

// static void	check_map_closure(t_parsed_map *parsed_map)
// {
// 	char	*map;
// 	int		width;
// 	int		heigth;
// 	int		x;
// 	int		y;

// 	map = parsed_map->elems;
// 	width = parsed_map->width;
// 	heigth = parsed_map->heigth;
// 	x = 0;
// 	while (x < width)
// 	{
// 		if (map[x] != E_WALL && map[x] != E_EMPTY)
// 			cub_parse_error(NULL, "Map is not closed (top border)\n");
// 		x++;
// 	}
// 	x = 0;
// 	while (x < width)
// 	{
// 		if (map[(heigth - 1) * (width + 1) + x] != E_WALL && map[(heigth - 1)
// 			* (width + 1) + x] != E_EMPTY)
// 			cub_parse_error(NULL, "Map is not closed (bottom border)\n");
// 		x++;
// 	}
// 	y = 0;
// 	while (y < heigth)
// 	{
// 		if (map[y * (width + 1)] != E_WALL && map[y * (width + 1)] != E_EMPTY)
// 			cub_parse_error(NULL, "Map is not closed (left border)\n");
// 		if (map[y * (width + 1) + width - 1] != E_WALL && map[y * (width + 1)
// 			+ width - 1] != E_EMPTY)
// 			cub_parse_error(NULL, "Map is not closed (right border)\n");
// 		y++;
// 	}
// }

void	cub_check_file(t_data *data, char *filename)
{
	int		fd;
	int		len;

	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(filename + len - 4, ".cub", 4))
		cub_handle_fatal(data, MSG_PARSE_INVALID_FILENAME);
	fd = open(filename, R_OK);
	if (fd == -1)
		cub_handle_fatal(data, MSG_PARSE_CANT_OPEN);
	close(fd);
}

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

void	cub_check_map_not_started(t_data *data, char *line)
{
	if (cub_is_map_line(line))
	{
		if (!cub_are_infos_filled(data))
		{
			free(line);
			close(data->parsed_map->fd);
			cub_handle_fatal(data, MSG_PARSE_MISSING);
		}
	}
}

void	cub_add_ceiling_or_floor_color(t_data *data, char *trimmed, char *line, bool *has_matched)
{
	unsigned int	color;

	*has_matched = true;
	if (cub_parse_color(trimmed + 2, &color))
		cub_handle_fatal_parse(data, data->parsed_map->fd, line, MSG_PARSE_INVALID_COLOR);
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

void	cub_init_cardinal_codes(char **codes)
{
	codes[0] = "NO ";
	codes[1] = "SO ";
	codes[2] = "WE ";
	codes[3] = "EA ";
}

void	cub_handle_matching_code(t_data *data, int i, char *line, char *trimmed)
{
	data->parsed_map->paths[i] = ft_strdup(trimmed + 3);
	if (!data->parsed_map->paths[i])
		cub_handle_fatal_parse(data, data->parsed_map->fd, line , MSG_ALLOC);
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
MSG_PARSE_INVALID_LINE);
}

void	cub_parse_infos(t_data *data, char **line)
{
	// char	*line;
	// char	*trimmed;
	// char	**paths;

	*line = get_next_line(data->parsed_map->fd);
	if (!*line)
		cub_handle_fatal_parse(data, data->parsed_map->fd, *line, MSG_PARSE_MISSING);
	while (*line && !cub_are_infos_filled(data))
	{
		cub_check_map_not_started(data, *line);
		if (ft_strcmp(*line, "\n"))
			cub_try_add_texture_paths_and_colors(data, *line);
		free(*line);
		*line = get_next_line(data->parsed_map->fd);
	}
}

void	cub_update_dimension(t_data *data, char **line, int *max_w)
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
	// int		width;
	int		max_w;
	char	*line;

	max_w = 0;
	data->parsed_map->fd = open(filename, R_OK);
	if (data->parsed_map->fd == -1)
		cub_handle_fatal_parse(data, data->parsed_map->fd, NULL, MSG_PARSE_CANT_OPEN);
	line = get_next_line(data->parsed_map->fd);
	if (!line)
		cub_handle_fatal_parse(data, data->parsed_map->fd, line, MSG_PARSE_MISSING);
	while (line && !cub_is_map_line(line))
	{
		free(line);
		line = get_next_line(data->parsed_map->fd);
	}
	if (!line)
		cub_handle_fatal_parse(data, data->parsed_map->fd, line, MSG_PARSE_MISSING);
	while (line && cub_is_map_line(line))
	{
		cub_update_dimension(data, &line, &max_w);
	}
	free(line);
	close(data->parsed_map->fd);
	data->parsed_map->width = max_w;
}

int	cub_parse_map(t_data *data, char **line)
{
	char	*trimmed;

	while (*line && !ft_strcmp(*line, "\n"))
	{
		free(*line);
		*line = get_next_line(data->parsed_map->fd);
	}
	while (*line)
	{
		trimmed = cub_trim_full(*line);
		if (!trimmed)
			cub_handle_fatal_parse(data, data->parsed_map->fd, *line, MSG_PARSE_EMPTY_LINE_MAP);
		else if (cub_is_map_line(trimmed))
			cub_add_map_line(data, data->parsed_map, *line);
		else
			cub_handle_fatal_parse(data, data->parsed_map->fd, *line, MSG_PARSE_UNKNOWN);
		free(*line);
		*line = get_next_line(data->parsed_map->fd);
	}
	free(*line);
	return (EXIT_SUCCESS);
}

int	cub_parse_file(char *filename, t_data *data)
{
	// int				fd;
	// t_parsed_map	*map;
	// int				map_started;
	// char			*l;
	// int				lenl;
	char	*line;

	line = NULL;
	cub_check_file(data, filename);
	cub_measure_map(data, filename);
	data->parsed_map->fd = open(filename, R_OK);
	data->parsed_map->elems = ft_calloc(data->parsed_map->heigth * \
data->parsed_map->width + 1, sizeof(char));
	if (!data->parsed_map->elems)
		cub_handle_fatal_parse(data, data->parsed_map->fd, NULL, MSG_ALLOC);
	cub_parse_infos(data, &line);
	cub_parse_map(data, &line);
	close(data->parsed_map->fd);
	cub_find_player(data->parsed_map);
	check_map_closed(data, data->parsed_map);
	data->parsed_map->elems[data->parsed_map->player_pos] = '0';
	return (EXIT_SUCCESS);
}
