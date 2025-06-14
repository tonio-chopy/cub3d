/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:51 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/12 20:27:59 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_bonus.h"

char	*cub_trim_map(char *line)
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

char	*cub_trim_full(char *line)
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

bool	cub_is_map_line(char *line)
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
			&& *trimmed != E_EMPTY && *trimmed != E_GOAL_LEFT
			&& *trimmed != E_GOAL_CENTER && *trimmed != E_GOAL_RIGHT
			&& *trimmed != E_BALL)
			return (false);
		trimmed++;
	}
	return (true);
}

void	cub_add_map_line(t_data *data, t_parsed_map *parsed_map, char *line,
		int i)
{
	size_t	len;
	char	*cleaned;
	size_t	x;
	int		start_i;

	(void)data;
	start_i = i * parsed_map->width;
	cleaned = cub_trim_map(line);
	len = ft_strlen(cleaned);
	x = 0;
	while (x++ < len)
		ft_memcpy(&parsed_map->elems[start_i], cleaned, len);
	x--;
	while ((int)x < parsed_map->width)
		parsed_map->elems[start_i + x++] = ' ';
}
