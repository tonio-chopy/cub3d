/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos_textures_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 07:52:15 by tonio-chopy       #+#    #+#             */
/*   Updated: 2025/06/28 18:30:17 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static char	*cub_validate_and_trim_path(char *path_start, char *line,
		t_data *data)
{
	char	*path_end;
	size_t	path_len;
	char	*path;

	if (!*path_start)
		cub_handle_fatal_parse(data, data->parsed_map->fd, line, MSP_MTP);
	path_end = path_start;
	while (*path_end && *path_end != ' ' && *path_end != '\t')
		path_end++;
	while (*path_end == ' ' || *path_end == '\t')
		path_end++;
	if (*path_end)
		cub_handle_fatal_parse(data, data->parsed_map->fd, line, MSP_ECT);
	path_len = path_end - path_start;
	while (path_len > 0 && (path_start[path_len - 1] == ' '
			|| path_start[path_len - 1] == '\t'))
		path_len--;
	path = ft_substr(path_start, 0, path_len);
	return (path);
}

void	cub_check_texture_path(t_data *data, int i, char *line,
		char *trimmed)
{
	char	*path_start;
	char	*path;
	int		fd;

	if (data->parsed_map->paths[i])
		cub_handle_fatal_parse(data, data->parsed_map->fd, line, MSP_DTP);
	path_start = trimmed + 2;
	while (*path_start == ' ' || *path_start == '\t')
		path_start++;
	path = cub_validate_and_trim_path(path_start, line, data);
	if (!path)
	{
		free(path);
		cub_handle_fatal_parse(data, data->parsed_map->fd, line, MSG_ALLOC);
	}
	fd = open(path, R_OK);
	if (fd == -1)
	{
		free(path);
		cub_handle_fatal_parse(data, data->parsed_map->fd, line, MSP_IVP);
	}
	close(fd);
	data->parsed_map->paths[i] = path;
}
