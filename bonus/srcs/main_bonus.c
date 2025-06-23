/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:36:24 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/23 16:32:23 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	if (check_args(ac, env) == false)
		return (EXIT_FAILURE);
	data = cub_init_data(av);
	if (!data)
		return (EXIT_FAILURE);
	cub_init_graphics(data);
	cub_init_sprite(data);
	cub_draw_ceiling_and_floor(data);
	cub_draw_minimap(data);
	cub_draw_player(data);
	init_random();
	cub_draw_walls(data);
	cub_draw_ball(data);
	cub_draw_flags(data);
	cub_init_hooks(data);
	cub_cpy_with_transparency(data->walls->img, data->minimap->map,
		data->minimap->map->location->x, data->minimap->map->location->y);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->walls->img->img, 0, 0);
	mlx_loop(data->mlx->mlx);
	cub_clean_data(data);
	return (EXIT_SUCCESS);
}

void	debug_elems(t_parsed_map *map, char *elems)
{
	int	y;

	y = 0;
	while (elems && y < map->heigth)
	{
		write(1, elems, map->width);
		printf("\n");
		elems += map->width;
		y++;
	}
}
