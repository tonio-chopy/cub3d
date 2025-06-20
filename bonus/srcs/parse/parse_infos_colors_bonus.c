/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos_colors_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 07:52:15 by tonio-chopy       #+#    #+#             */
/*   Updated: 2025/06/20 17:14:50 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static unsigned int	cub_parse_color_part(t_data *data, char *color_part,
		char *line)
{
	unsigned int	color;

	if (cub_parse_color(color_part, &color))
		cub_handle_fatal_parse(data, data->parsed_map->fd, line,
			MSP_INVALID_COLOR);
	return (color);
}

void	cub_add_ceiling_or_floor_color(t_data *data, char *trimmed,
		char *line, bool *has_matched)
{
	unsigned int	color;
	char			*color_part;

	*has_matched = true;
	color_part = trimmed + 1;
	while (*color_part == ' ' || *color_part == '\t')
		color_part++;
	color = cub_parse_color_part(data, color_part, line);
	if (!ft_strncmp(trimmed, "F", 1))
		cub_set_floor_color(data, line, color);
	else
		cub_set_ceiling_color(data, line, color);
}
