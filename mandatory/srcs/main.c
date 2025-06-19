/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/19 21:10:27 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
	cub_init_graphics(data);
	cub_draw_ceiling_and_floor(data);
	cub_draw_walls(data);
	cub_init_hooks(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->walls->img->img, 0, 0);
	mlx_loop(data->mlx->mlx);
	cub_clean_data(data);
	return (EXIT_SUCCESS);
}
