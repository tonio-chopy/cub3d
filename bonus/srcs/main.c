/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:36:24 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/17 20:59:27 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

bool	check_args(int ac, char **env)
{
	if (ac != 2)
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

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	if (check_args(ac, env) == false)
		return (EXIT_FAILURE);
	data = cub_init_data(av);
	if (!data)
		return (EXIT_FAILURE);
	cub_init_graphics(data);
	cub_draw_ceiling_and_floor(data);
	cub_draw_minimap(data);
	cub_draw_player(data);
	init_random();
	cub_draw_walls(data);
	cub_draw_ball(data);
	cub_init_hooks(data);
	cub_cpy_with_transparency(data->walls->img, data->minimap->map,
		data->minimap->map->location->x, data->minimap->map->location->y);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->walls->img->img, 0, 0);
	mlx_loop(data->mlx->mlx);
	cub_clean_data(data);
	return (EXIT_SUCCESS);
}
