/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:48:07 by alaualik          #+#    #+#             */
/*   Updated: 2025/05/16 21:51:45 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	cub_free_data(t_parsed_map *data)
{
	if (data->NOpath)
		free(data->NOpath);
	if (data->SOpath)
		free(data->SOpath);
	if (data->EApath)
		free(data->EApath);
	if (data->WEpath)
		free(data->WEpath);
}

int	main(int ac, char **av)
{
	t_parsed_map	data;

	if (ac != 2)
	{
		printf("Usage: %s <file.cub>\n", av[0]);
		return (-1);
	}
	if (!cub_is_valid_map_extension(av[1]))
	{
		printf("Error: File must have .cub extension\n");
		return (-1);
	}
	cub_init_data(&data);
	if (!parse_cub_file(&data, av[1]))
	{
		cub_free_data(&data);
		return (-1);
	}
	cub_free_data(&data);
	return (0);
}
