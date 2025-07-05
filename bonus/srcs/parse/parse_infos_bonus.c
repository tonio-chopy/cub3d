/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:44 by fpetit            #+#    #+#             */
/*   Updated: 2025/07/05 15:48:47 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static void	free_balls(t_data *data, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(data->balls[i]);
		i++;
	}
	free(data->balls);
	data->balls = NULL;
}

void	cub_init_sprite_infos(t_data *data)
{
	int	i;

	data->sprite_distance = ft_calloc(data->nb_ball, sizeof(double));
	if (!data->sprite_distance)
		cub_handle_fatal(data, MSG_ALLOC);
	data->balls = ft_calloc(data->nb_ball, sizeof(t_sprite *));
	if (!data->balls)
		cub_handle_fatal(data, MSG_ALLOC);
	i = 0;
	while (i < data->nb_ball)
	{
		data->balls[i] = ft_calloc(1, sizeof(t_sprite));
		if (!data->balls[i])
		{
			free_balls(data, i);
			cub_handle_fatal(data, MSG_ALLOC);
		}
		data->balls[i]->sprite_nb = 5;
		data->balls[i]->elem = E_BALL_VISITED;
		data->balls[i]->transform_y = 0;
		data->balls[i]->transform_x = 0;
		i++;
	}
}

static bool	cub_is_valid_direction_codes(t_data *data,
										char *trimmed, char *line)
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
	if (ft_isblankornlstr(trimmed))
		return ;
	has_matched = cub_is_valid_direction_codes(data, trimmed, line);
	if (has_matched)
		return ;
	if (!has_matched)
		has_matched = cub_check_color_codes(data, trimmed, line);
	if (!has_matched)
		cub_handle_fatal_parse(data, data->parsed_map->fd, line, MSP_IVL);
}
