#include "test.h"

static char	*trim_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	char *end = str + ft_strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
		*end-- = 0;
	return (str);
}

static int	parse_color(char *str, unsigned int *color)
{
	int		r, g, b;
	char	**split = ft_split(str, ',');
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
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == 0)
		return (0);
	while (*line)
	{
		if (*line != E_WALL && *line != E_INSIDE &&
			*line != E_NORTH && *line != E_SOUTH &&
			*line != E_EAST && *line != E_WEST && *line != E_EMPTY)
			return (0);
		line++;
	}
	return (1);
}

static void	parse_error(t_data *data, char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	cub_clean_data(data);
	exit(EXIT_FAILURE);
}

static void	add_map_line(t_parsed_map *parsed_map, char *line)
{
	int	len = ft_strlen(line);
	char *new = malloc(parsed_map->nb_elems + len + 2);
	if (!new)
		return ;
	if (parsed_map->elems)
		ft_memcpy(new, parsed_map->elems, parsed_map->nb_elems);
	ft_memcpy(new + parsed_map->nb_elems, line, len);
	new[parsed_map->nb_elems + len] = '\n';
	new[parsed_map->nb_elems + len + 1] = 0;
	free(parsed_map->elems);
	parsed_map->elems = new;
	parsed_map->nb_elems += len + 1;
}

static void	find_player(t_parsed_map *parsed_map)
{
	int	i = 0;
	int	found = 0;
	while (parsed_map->elems && parsed_map->elems[i])
	{
		if (parsed_map->elems[i] == E_NORTH || parsed_map->elems[i] == E_SOUTH ||
			parsed_map->elems[i] == E_EAST || parsed_map->elems[i] == E_WEST)
		{
			if (found++)
				parse_error(NULL, "Multiple player positions!\n");
			parsed_map->player_orientation = parsed_map->elems[i];
			parsed_map->player_pos = i;
		}
		i++;
	}
	if (!found)
		parse_error(NULL, "No player position found!\n");
}

// Map closure: simple check (border lines only, for demo)
static void	check_map_closure(t_parsed_map *parsed_map)
{
	char	*map = parsed_map->elems;
	int		width = parsed_map->width;
	int		heigth = parsed_map->heigth;

	for (int x = 0; x < width; x++)
		if (map[x] != E_WALL && map[x] != E_EMPTY)
			parse_error(NULL, "Map is not closed (top border)\n");
	for (int x = 0; x < width; x++)
		if (map[(heigth - 1) * (width + 1) + x] != E_WALL && map[(heigth - 1) * (width + 1) + x] != E_EMPTY)
			parse_error(NULL, "Map is not closed (bottom border)\n");
	for (int y = 0; y < heigth; y++)
	{
		if (map[y * (width + 1)] != E_WALL && map[y * (width + 1)] != E_EMPTY)
			parse_error(NULL, "Map is not closed (left border)\n");
		if (map[y * (width + 1) + width - 1] != E_WALL && map[y * (width + 1) + width - 1] != E_EMPTY)
			parse_error(NULL, "Map is not closed (right border)\n");
	}
}

int	parse_cub_file(char *filename, t_data *data)
{
	FILE			*f;
	char			*line;
	size_t			len = 0;
	ssize_t			read;
	t_parsed_map	*map = data->parsed_map;
	int				map_started = 0, heigth = 0, width = 0;

	f = fopen(filename, "r");
	if (!f)
		parse_error(data, "Cannot open .cub file!\n");
	while ((read = getline(&line, &len, f)) != -1)
	{
		char *l = trim_spaces(line);
		// Correction : accepter les lignes vides partout avant la map (mais pas dans la map)
		if (*l == 0)
		{
			if (!map_started)
				continue;
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
			int lenl = ft_strlen(l);
			if (lenl > width)
				width = lenl;
		}
		else if (map_started && is_map_line(l))
		{
			add_map_line(map, l);
			heigth++;
			int lenl = ft_strlen(l);
			if (lenl > width)
				width = lenl;
		}
		else
			parse_error(data, "Unknown or misplaced element in .cub file\n");
	}
	fclose(f);
	map->width = width;
	map->heigth = heigth;

	find_player(map);
	check_map_closure(map);

	return (0);
}
