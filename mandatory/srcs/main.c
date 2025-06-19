/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/19 19:59:53 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

static void	replace_player_with_zero(t_parsed_map *map)
{
	if (map->elems && map->player_pos >= 0 && map->player_pos < map->nb_elems)
		map->elems[map->player_pos] = '0';
}

void	init_parsed_map(t_data *data)
{
	data->parsed_map = ft_calloc(1, sizeof(t_parsed_map));
	if (!data->parsed_map)
		cub_handle_fatal(data, MSG_ALLOC);
	data->parsed_map->paths = ft_calloc(4, sizeof(char *));
	if (!data->parsed_map->paths)
		cub_handle_fatal(data, MSG_ALLOC);
	data->parsed_map->has_ceiling = false;
	data->parsed_map->has_floor = false;
	data->parsed_map->heigth = 0;
	data->parsed_map->width = 0;
	data->parsed_map->nb_elems = 0;
}

t_data	*cub_init_data(int ac, char **av)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	if (!ft_strcmp(&(av[0][ft_strlen(av[0]) - 11]), BONUS_NAME))
		data->is_bonus = true;
	data->rotates_left = false;
	data->rotates_right = false;
	data->move_forward = false;
	data->move_backward = false;
	data->move_left = false;
	data->move_right = false;
	data->mlx = cub_init_mlx();
	if (!data->mlx)
		return (NULL);
	init_parsed_map(data);
	if (cub_parse_file(av[1], data))
		return (NULL);
	replace_player_with_zero(data->parsed_map);
	return (data);
}

bool	check_args(int ac, char **av, char **env)
{
	if (ac < 2 || (ac == 3 && (av[2][0] != '1' && av[2][0] != '2')))
	{
		ft_puterr(MSG_USAGE);
		return (false);
	}
	if (!env)
	{
		ft_puterr(MSG_EMPTY_ENV);
		return (false);
	}
	return (true);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (!check_args(ac, av, __environ))
		return (EXIT_FAILURE);
	data = cub_init_data(ac, av);
	if (!data)
	{
		cub_cleanup_audio();
		return (EXIT_FAILURE);
	}
	init_and_start_game(data);
	cub_cleanup_audio();
	cub_clean_data(data);
	return (EXIT_SUCCESS);
}
