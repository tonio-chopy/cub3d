/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 07:52:15 by tonio-chopy       #+#    #+#             */
/*   Updated: 2025/06/20 15:00:15 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static char	*cub_validate_and_trim_path(char *path_start, char *line,
		t_data *data)
{
	char	*path_end;
	size_t	path_len;

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
	return (ft_substr(path_start, 0, path_len));
}

void	cub_handle_matching_code(t_data *data, int i, char *line,
		char *trimmed)
{
	char	*path_start;
	char	*path;

	if (data->parsed_map->paths[i])
		cub_handle_fatal_parse(data, data->parsed_map->fd, line,
			"Duplicate texture path");
	path_start = trimmed + 2;
	while (*path_start == ' ' || *path_start == '\t')
		path_start++;
	path = cub_validate_and_trim_path(path_start, line, data);
	if (!path)
		cub_handle_fatal_parse(data, data->parsed_map->fd, line, MSG_ALLOC);
	data->parsed_map->paths[i] = path;
}
