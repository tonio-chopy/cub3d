/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_col.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:30:34 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/17 20:35:14 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

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

static int	cub_count_and_trim(char **split, char *trimmed_parts[3], \
int *tcount)
{
	*tcount = cub_count_elements(split);
	if (*tcount != 3 || !split[0] || !split[1] || !split[2])
	{
		cub_clean2d((void **)split, *tcount, (1 << *tcount) - 1, true);
		return (EXIT_FAILURE);
	}
	trimmed_parts[0] = trim_whitespace(split[0]);
	trimmed_parts[1] = trim_whitespace(split[1]);
	trimmed_parts[2] = trim_whitespace(split[2]);
	if (!trimmed_parts[0][0] || !trimmed_parts[1][0] || !trimmed_parts[2][0])
	{
		cub_clean2d((void **)split, *tcount, (1 << *tcount) - 1, true);
		return (EXIT_FAILURE);
	}
	if (!cub_is_valid_number(trimmed_parts[0]) || !cub_is_valid_number\
(trimmed_parts[1]) || !cub_is_valid_number(trimmed_parts[2]))
	{
		cub_clean2d((void **)split, *tcount, (1 << *tcount) - 1, true);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	cub_parse_color(char *str, unsigned int *color)
{
	char	**split;
	char	*trimmed_parts[3];
	int		code;
	int		total_count;
	t_color	col;

	if (has_consecutive_commas(str) || count_commas(str) != 2)
		return (EXIT_FAILURE);
	split = ft_split(str, ',');
	if (!split)
		return (EXIT_FAILURE);
	code = cub_count_and_trim(split, trimmed_parts, &total_count);
	col.r = ft_atoi(trimmed_parts[0]);
	col.g = ft_atoi(trimmed_parts[1]);
	col.b = ft_atoi(trimmed_parts[2]);
	if (col.r < 0 || col.r > 255 || col.g < 0 || col.g > 255 || col.b < 0 \
|| col.b > 255)
	{
		cub_clean2d((void **)split, total_count, (1 << total_count) - 1, true);
		return (EXIT_FAILURE);
	}
	*color = (col.r << 16) | (col.g << 8) | col.b;
	cub_clean2d((void **)split, total_count, (1 << total_count) - 1, true);
	return (EXIT_SUCCESS);
}
