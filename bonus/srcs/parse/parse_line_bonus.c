/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:46:51 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/20 17:15:25 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

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

static bool	cub_is_not_map_elem_manda(char c)
{
	return (c != E_WALL && c != E_INSIDE && c != E_NORTH
			&& c != E_SOUTH && c != E_EAST && c != E_WEST
			&& c != E_EMPTY);
}

bool	cub_is_map_line(char *line, bool is_bonus)
{
	char	*trimmed;

	trimmed = cub_trim_full(line);
	while (*trimmed == ' ' || *trimmed == '\t')
		trimmed++;
	if (*trimmed == 0)
		return (false);
	while (*trimmed)
	{
		if (is_bonus && cub_is_not_map_elem_manda(*trimmed) 
&& *trimmed != E_GOAL_CENTER && *trimmed != E_GOAL_LEFT && *trimmed != E_GOAL_RIGHT && *trimmed != E_BALL)
			return (false);
		trimmed++;
	}
	return (true);
}

void	cub_add_map_line(t_data *data, t_parsed_map *parsed_map, \
char *line, int i)
{
	size_t	len;
	char	*cleaned;
	size_t	x;
	int		start_i;

	(void) data;
	start_i = i * parsed_map->width;
	cleaned = cub_trim_map(line);
	len = ft_strlen(cleaned);
	x = 0;
	while (x++ < len)
		ft_memcpy(&parsed_map->elems[start_i], cleaned, len);
	x--;
	while ((int) x < parsed_map->width)
		parsed_map->elems[start_i + x++] = ' ';
}
