/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:03:32 by alaualik          #+#    #+#             */
/*   Updated: 2025/05/16 17:46:30 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	cub_init_data(t_parsed_map *data)
{
	data->NOpath = NULL;
	data->SOpath = NULL;
	data->EApath = NULL;
	data->WEpath = NULL;
	data->has_no = false;
	data->has_so = false;
	data->has_ea = false;
	data->has_we = false;
	data->has_floor = false;
	data->has_ceiling = false;
}

bool	cub_parse_texture(t_parsed_map *data, char *line, const char *prefix)
{
	char	**target_path;
	bool	*has_texture;
	char	*path;

	target_path = NULL;
	has_texture = NULL;
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		target_path = &data->NOpath;
		has_texture = &data->has_no;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		target_path = &data->SOpath;
		has_texture = &data->has_so;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		target_path = &data->EApath;
		has_texture = &data->has_ea;
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		target_path = &data->WEpath;
		has_texture = &data->has_we;
	}
	else
		return (false);
	if (*has_texture)
	{
		printf("Error : %s already defined.\n", prefix);
		return (false);
	}
	path = line + 2;
	while (*path == ' ')
		path++;
	*target_path = malloc(ft_strlen(path) + 1);
	if (!*target_path)
	{
		perror("Error : malloc.\n");
		return (false);
	}
	ft_strcpy(*target_path, path);
	*has_texture = true;
	return (true);
}

bool	cub_parse_color(t_parsed_map *data, char *line, const char prefix)
{
	int		*target_color;
	bool	*has_color;
	char	*rgb_str;
	char	*comma1;
	char	*comma2;
	int		r;
	int		g;
	int		b;

	target_color = NULL;
	has_color = NULL;
	if (line[0] == 'F' && line[1] == ' ')
	{
		target_color = data->floor_color;
		has_color = &data->has_floor;
	}
	else if (line[0] == 'C' && line[1] == ' ')
	{
		target_color = data->ceiling_color;
		has_color = &data->has_ceiling;
	}
	else
		return (false);
	if (*has_color)
	{
		printf("Error : Color %c already defined.\n", prefix);
		return (false);
	}
	rgb_str = line + 1;
	while (*rgb_str == ' ')
		rgb_str++;
	comma1 = ft_strchr(rgb_str, ',');
	comma2 = NULL;
	if (comma1 != NULL)
		comma2 = ft_strchr(comma1 + 1, ',');
	if (comma1 == NULL || comma2 == NULL || ft_strchr(comma2 + 1, ',') != NULL)
	{
		printf("Error : Format RGB invalid for %c.\n", prefix);
		return (false);
	}
	r = ft_atoi(rgb_str);
	g = ft_atoi(comma1 + 1);
	b = ft_atoi(comma2 + 1);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		printf("Error : RGB valurd invalid for %c.\n", prefix);
		return (false);
	}
	target_color[0] = r;
	target_color[1] = g;
	target_color[2] = b;
	*has_color = true;
	return (true);
}

bool	cub_is_valid_map_extension(char *file)
{
	const char	*dot;

	dot = ft_strrchr(file, '.');
	return (dot && !ft_strcmp(dot, ".cub"));
}

bool	cub_parse_file(t_parsed_map *data, const char *filename)
{
	int		fd;
	char	*line;
	bool	parsing_success;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Error\nopen");
		return (false);
	}
	parsing_success = true;
	while (parsing_success && (line = get_next_line(fd)) != NULL)
	{
		line = clean_line(line);
		if (line[0] != '\0')
		{
			if (!parse_texture(data, line, "NO") && !parse_texture(data, line,
					"SO") && !parse_texture(data, line, "EA")
				&& !parse_texture(data, line, "WE") && !parse_color(data, line,
					'F') && !parse_color(data, line, 'C') && !is_map_line(line))
			{
				printf("Error : Invalid line: %s.", line);
				parsing_success = false;
			}
		}
		free(line);
	}
	close(fd);
	if (parsing_success && (!data->has_no || !data->has_so || !data->has_ea
			|| !data->has_we || !data->has_floor || !data->has_ceiling))
	{
		printf("Error : Missing required elements in .cub file.\n");
		parsing_success = false;
	}
	return (parsing_success);
}
