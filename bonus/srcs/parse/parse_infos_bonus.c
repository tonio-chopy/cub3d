/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:44 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/21 18:54:04 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static bool	cub_is_valid_direction_codes(t_data *data, char *trimmed, char *line)
{
	int		i;

	i = 0;
	while (i < 4)
	{
		if (!ft_strncmp(trimmed, data->parsed_map->codes[i], 2) \
&& (trimmed[2] == ' ' || trimmed[2] == '\t'))
		{
			cub_check_texture_path(data, i, line, trimmed);
			return (true);
		}
		else if (!ft_strncmp(trimmed, data->parsed_map->codes[i], 2))
		{
			cub_handle_fatal_parse(data, data->parsed_map->fd, line, MSP_MTP);
		}
		i++;
	}
	return (false);
}

static bool	cub_check_color_codes(t_data *data, char *trimmed, char *line)
{
	bool	has_matched;

	has_matched = false;
	if ((!ft_strncmp(trimmed, "F", 1) && (trimmed[1] == ' '
				|| trimmed[1] == '\t')) || (!ft_strncmp(trimmed, "C", 1)
			&& (trimmed[1] == ' ' || trimmed[1] == '\t')))
	{
		cub_add_ceiling_or_floor_color(data, trimmed, line, &has_matched);
	}
	return (has_matched);
}

void	cub_try_add_texture_paths_and_colors(t_data *data, char *line)
{
	char	*trimmed;
	bool	has_matched;

	trimmed = cub_trim_full(line);
	has_matched = cub_is_valid_direction_codes(data, trimmed, line);
	if (has_matched)
		return ;
	if (!has_matched)
		has_matched = cub_check_color_codes(data, trimmed, line);
	if (!has_matched)
		cub_handle_fatal_parse(data, data->parsed_map->fd, line, MSP_IVL);
}
