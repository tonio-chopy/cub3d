/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 17:27:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/05/18 18:40:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

// Remplace les tabs par des espaces (pour le parsing map et infos)
static void	replace_tabs(char *str)
{
	while (str && *str)
	{
		if (*str == '\t')
			*str = ' ';
		str++;
	}
}

static char	*trim_spaces(char *str)
{
	char	*end;

	replace_tabs(str);
	while (*str == ' ')
		str++;
	end = str + ft_strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\n'))
		*end-- = 0;
	return (str);
}

static int	parse_color(char *str, unsigned int *color)
{
	char	**split;
	int		r, g, b;

	replace_tabs(str);
	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
		return (1);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (cub_clean2d((void **)split, 3, 0, true), 1);
	*color = (r << 16) | (g << 8) | b;
	cub_clean2d((void **)split, 3, 0, true);
	return (0);
}

static int	is_map_line(const char *line)
{
	while (*line == ' ')
		line++;
	if (*line == 0)
		return (0);
	while (*line)
	{
		if (*line != E_WALL && *line != E_INSIDE && *line != E_NORTH
			&& *line != E_SOUTH && *line != E_EAST && *line != E_WEST
			&& *line != E_EMPTY)
			return (0);
		line++;
	}
	return (1);
}

static void	parse_error(t_data *data, char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	if (data)
		cub_clean_data(data);
	exit(EXIT_FAILURE);
}

static void	add_map_line(t_parsed_map *parsed_map, char *line)
{
	int		len;
	char	*new;

	len = ft_strlen(line);
	new = malloc(parsed_map->nb_elems + len + 2);
	if (!new)
		parse_error(NULL, "malloc failed (add_map_line)\n");
	if (parsed_map->elems)
		ft_memcpy(new, parsed_map->elems, parsed_map->nb_elems);
	ft_memcpy(new + parsed_map->nb_elems, line, len);
	new[parsed_map->nb_elems + len] = '\n';
	new[parsed_map->nb_elems + len + 1] = 0;
	free(parsed_map->elems);
	parsed_map->elems = new;
	parsed_map->nb_elems += len + 1;
}

// Retourne le nombre de joueurs trouvés et vérifie qu'il est bien dans la map
static int	find_player(t_parsed_map *parsed_map)
{
	int	i;
	int	found;
	int	row;
	int	col;
	int	width;

	i = 0;
	found = 0;
	width = parsed_map->width;
	while (parsed_map->elems && parsed_map->elems[i])
	{
		if (parsed_map->elems[i] == E_NORTH || parsed_map->elems[i] == E_SOUTH
			|| parsed_map->elems[i] == E_EAST || parsed_map->elems[i] == E_WEST)
		{
			row = i / (width + 1); // +1 pour '\n'
			col = i % (width + 1);
			// On vérifie que le joueur n'est pas sur un '\n'
			if (col >= width)
				parse_error(NULL, "Player out of map bounds!\n");
			parsed_map->player_orientation = parsed_map->elems[i];
			parsed_map->player_pos = i;
			found++;
		}
		i++;
	}
	return (found);
}

// Flood fill utilitaire pour la fermeture de map
static int flood_check(char *map, int width, int height, int i, char *visited)
{
	int	x = i % (width + 1);
	int	y = i / (width + 1);

	// Hors map ou dans un espace vide (pas de mur, pas d'intérieur) -> erreur
	if (x < 0 || y < 0 || x >= width || y >= height)
		return (0);
	if (map[i] == E_WALL || map[i] == 'X' || visited[i])
		return (1);
	if (map[i] == E_EMPTY || map[i] == '\n')
		return (1);

	visited[i] = 1;
	int result = 1;
	// On explore les 4 voisins
	result &= flood_check(map, width, height, i + 1, visited);
	result &= flood_check(map, width, height, i - 1, visited);
	result &= flood_check(map, width, height, i + (width + 1), visited);
	result &= flood_check(map, width, height, i - (width + 1), visited);
	return result;
}

// Vérifie la fermeture de la map avec un flood fill (robuste)
static void	check_map_closure(t_parsed_map *parsed_map)
{
	char	*map = parsed_map->elems;
	int		width = parsed_map->width;
	int		height = parsed_map->heigth;
	char	*visited;
	int		i;

	if (!map || width <= 2 || height <= 2)
		parse_error(NULL, "Map size invalid!\n");

	visited = ft_calloc(parsed_map->nb_elems + 1, 1);
	if (!visited)
		parse_error(NULL, "malloc failed (closure check)\n");

	// Chercher une première case intérieure de la map pour flood
	for (i = 0; map[i]; i++)
	{
		if (map[i] == E_INSIDE || map[i] == E_NORTH || map[i] == E_SOUTH
			|| map[i] == E_EAST || map[i] == E_WEST)
			break;
	}
	if (!map[i])
	{
		free(visited);
		parse_error(NULL, "No inside cell found for closure check!\n");
	}
	if (!flood_check(map, width, height, i, visited))
	{
		free(visited);
		parse_error(NULL, "Map is not closed!\n");
	}
	free(visited);
}

int	parse_cub_file(char *filename, t_data *data)
{
	FILE			*f;
	char			*line;
	size_t			len;
	ssize_t			read;
	t_parsed_map	*map;
	int				map_started;
	char			*l;
	int				lenl;
	int				heigth;
	int				width;
	int				player_count;

	len = 0;
	map = data->parsed_map;
	map_started = 0, heigth = 0, width = 0;
	f = fopen(filename, "r");
	if (!f)
		parse_error(data, "Cannot open .cub file!\n");
	while ((read = getline(&line, &len, f)) != -1)
	{
		replace_tabs(line);
		l = trim_spaces(line);
		if (*l == 0)
		{
			if (!map_started)
				continue ;
			else
				parse_error(data, "Empty line in map content\n");
		}
		if (!map_started && !ft_strncmp(l, "NO ", 3))
			map->NOpath = ft_strdup(l + 3);
		else if (!map_started && !ft_strncmp(l, "SO ", 3))
			map->SOpath = ft_strdup(l + 3);
		else if (!map_started && !ft_strncmp(l, "WE ", 3))
			map->WEpath = ft_strdup(l + 3);
		else if (!map_started && !ft_strncmp(l, "EA ", 3))
			map->EApath = ft_strdup(l + 3);
		else if (!map_started && !ft_strncmp(l, "F ", 2))
		{
			if (parse_color(l + 2, &map->floor_color))
				parse_error(data, "Invalid floor color\n");
		}
		else if (!map_started && !ft_strncmp(l, "C ", 2))
		{
			if (parse_color(l + 2, &map->ceiling_color))
				parse_error(data, "Invalid ceiling color\n");
		}
		else if (is_map_line(l))
		{
			map_started = 1;
			add_map_line(map, l);
			heigth++;
			lenl = ft_strlen(l);
			if (lenl > width)
				width = lenl;
		}
		else if (map_started && is_map_line(l))
		{
			add_map_line(map, l);
			heigth++;
			lenl = ft_strlen(l);
			if (lenl > width)
				width = lenl;
		}
		else
			parse_error(data, "Unknown or misplaced element in .cub file\n");
	}
	fclose(f);
	map->width = width;
	map->heigth = heigth;
	player_count = find_player(map);
	if (player_count == 0)
		parse_error(NULL, "No player position found!\n");
	if (player_count > 1)
		parse_error(NULL, "Multiple player positions!\n");
	check_map_closure(map);
	return (0);
}
