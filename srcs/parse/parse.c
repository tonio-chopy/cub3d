#include "test.h"

void    read_map(t_data *data, char *file)
{
    t_parsed_map *map;
}

bool	cub_is_valid_map_extension(char *file)
{
	const char	*dot;

	dot = ft_strrchr(file, '.');
	return (dot && !ft_strcmp(dot, ".cub"));
}

int main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Error : Usage -> ./cub3D <file.cub>\n");
		return (-1);
	}
	if (!cub_is_valid_map_extension(av[1]))
	{
		printf("Error : file must have extension .cub\n");
		return (-1);
	}
}
