/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:59 by fpetit            #+#    #+#             */
/*   Updated: 2025/05/21 17:47:02 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static bool	is_valid_number(char *str)
{
	int	i;

	if (!str || !*str)
		return (false);
	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

static bool	has_consecutive_commas(char *str)
{
	int	i;

	if (!str)
		return (true);
	i = 0;
	while (str[i])
	{
		if (str[i] == ',' && str[i + 1] == ',')
			return (true);
		if (str[i] == ',' && (i == 0 || str[i + 1] == '\0'))
			return (true);
		i++;
	}
	return (false);
}

static int	count_commas(char *str)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

static int	count_elements(char **split)
{
	int	count;

	count = 0;
	if (!split)
		return (0);
	while (split[count])
		count++;
	return (count);
}

static char	*trim_whitespace(char *str)
{
	char	*end;

	if (!str)
		return (NULL);
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == 0)
		return (str);
	end = str + ft_strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t'))
		end--;
	end[1] = '\0';
	return (str);
}

int	cub_parse_color(char *str, unsigned int *color)
{
	char	**split;
	char	*trimmed_parts[3];
	int		r;
	int		g;
	int		b;
	int		total_count;

	if (has_consecutive_commas(str) || count_commas(str) != 2)
		return (EXIT_FAILURE);
	split = ft_split(str, ',');
	if (!split)
		return (EXIT_FAILURE);
	total_count = count_elements(split);
	if (total_count != 3 || !split[0] || !split[1] || !split[2])
	{
		cub_clean2d((void **)split, total_count, (1 << total_count) - 1, true);
		return (EXIT_FAILURE);
	}
	trimmed_parts[0] = trim_whitespace(split[0]);
	trimmed_parts[1] = trim_whitespace(split[1]);
	trimmed_parts[2] = trim_whitespace(split[2]);
	if (!trimmed_parts[0][0] || !trimmed_parts[1][0] || !trimmed_parts[2][0])
	{
		cub_clean2d((void **)split, total_count, (1 << total_count) - 1, true);
		return (EXIT_FAILURE);
	}
	if (!is_valid_number(trimmed_parts[0]) || !is_valid_number(trimmed_parts[1]) || !is_valid_number(trimmed_parts[2]))
	{
		cub_clean2d((void **)split, total_count, (1 << total_count) - 1, true);
		return (EXIT_FAILURE);
	}
	r = ft_atoi(trimmed_parts[0]);
	g = ft_atoi(trimmed_parts[1]);
	b = ft_atoi(trimmed_parts[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		cub_clean2d((void **)split, total_count, (1 << total_count) - 1, true);
		return (EXIT_FAILURE);
	}
	*color = (r << 16) | (g << 8) | b;
	cub_clean2d((void **)split, total_count, (1 << total_count) - 1, true);
	return (EXIT_SUCCESS);
}

void	cub_compute_adjacent_indexes_x(t_parsed_map *map, int i, int *left_i, \
int *right_i)
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

void	cub_compute_adjacent_indexes_y(t_parsed_map *map, int i, int *up_i, \
int *down_i)
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

void	cub_check_map_not_started(t_data *data, char *line)
{
	if (cub_is_map_line(line))
	{
		if (!cub_are_infos_filled(data))
		{
			free(line);
			close(data->parsed_map->fd);
			cub_handle_fatal(data, MSP_MISSING);
		}
	}
}
