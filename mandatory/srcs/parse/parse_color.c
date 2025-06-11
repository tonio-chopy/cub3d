/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonio-chopy <tonio-chopy@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 07:07:00 by tonio-chopy       #+#    #+#             */
/*   Updated: 2025/06/11 07:07:00 by tonio-chopy      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static int	validate_rgb_values(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	parse_rgb_components(char **trimmed_parts, int *r, int *g, int *b)
{
	if (!is_valid_number(trimmed_parts[0]) || !is_valid_number(trimmed_parts[1])
		|| !is_valid_number(trimmed_parts[2]))
		return (EXIT_FAILURE);
	*r = ft_atoi(trimmed_parts[0]);
	*g = ft_atoi(trimmed_parts[1]);
	*b = ft_atoi(trimmed_parts[2]);
	return (EXIT_SUCCESS);
}

static int	process_color_split(char **split, unsigned int *color)
{
	char	*trimmed_parts[3];
	int		r;
	int		g;
	int		b;
	int		total_count;

	total_count = count_elements(split);
	if (total_count != 3 || !split[0] || !split[1] || !split[2])
		return (EXIT_FAILURE);
	trimmed_parts[0] = trim_whitespace(split[0]);
	trimmed_parts[1] = trim_whitespace(split[1]);
	trimmed_parts[2] = trim_whitespace(split[2]);
	if (!trimmed_parts[0][0] || !trimmed_parts[1][0] || !trimmed_parts[2][0])
		return (EXIT_FAILURE);
	if (parse_rgb_components(trimmed_parts, &r, &g, &b) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (validate_rgb_values(r, g, b) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	*color = (r << 16) | (g << 8) | b;
	return (EXIT_SUCCESS);
}

int	cub_parse_color(char *str, unsigned int *color)
{
	char	**split;
	int		total_count;
	int		result;

	if (has_consecutive_commas(str) || count_commas(str) != 2)
		return (EXIT_FAILURE);
	split = ft_split(str, ',');
	if (!split)
		return (EXIT_FAILURE);
	total_count = count_elements(split);
	result = process_color_split(split, color);
	cub_clean2d((void **)split, total_count, (1 << total_count) - 1, true);
	return (result);
}
