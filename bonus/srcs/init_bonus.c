/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 20:54:43 by fpetit            #+#    #+#             */
/*   Updated: 2025/07/03 19:54:24 by fpetit           ###   ########.fr       */
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

static void	init_parsed_map(t_data *data)
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
	data->parsed_map->opened_door_index = -1;
	data->parsed_map->fd = -1;
	cub_init_cardinal_codes(data->parsed_map->codes);
}

t_data	*cub_init_data(char **av)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	if (!ft_strcmp(&(av[0][ft_strlen(av[0]) - 11]), BONUS_NAME))
		data->is_bonus = true;
	data->zbuffer = ft_calloc(WIN_W, sizeof(double));
	if (!data->zbuffer)
		cub_handle_fatal(data, MSG_ALLOC);
	data->rotates_left = false;
	data->rotates_right = false;
	data->move_forward = false;
	data->move_backward = false;
	data->move_left = false;
	data->move_right = false;
	cub_init_mlx(data);
	if (!data->mlx)
		cub_handle_fatal(data, MSG_ALLOC);
	init_parsed_map(data);
	if (cub_parse_file(av[1], data) == EXIT_FAILURE)
		cub_handle_fatal(data, MSP_ERR);
	return (data);
}

void	cub_init_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx->mlx, &cub_refresh, data);
	mlx_hook(data->mlx->win, KeyPress, KeyPressMask, &cub_handle_keypress,
		data);
	mlx_hook(data->mlx->win, KeyRelease, KeyReleaseMask, &cub_handle_keyrelease,
		data);
	mlx_hook(data->mlx->win, DestroyNotify, NoEventMask, &handle_click_on_close,
		(void *)data);
	mlx_hook(data->mlx->win, MotionNotify, PointerMotionMask,
		&handle_mouse_rotate, (void *)data);
}
