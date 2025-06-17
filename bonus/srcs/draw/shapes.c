/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:34:27 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/17 16:19:38 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_bonus.h"

void	cub_draw_ceiling_and_floor(t_data *data)
{
	t_vec	*coord;
	t_shape	rect;

	coord = cub_init_vec_double(0, 0);
	init_shape(coord, WIN_W, RECTANGLE, &rect);
	rect.heigth = (double)WIN_H * data->walls->ceiling_ratio;
	rect.color = data->parsed_map->ceiling_color;
	cub_draw_rect(data->walls->img, &rect);
	rect.start->yd = rect.heigth;
	rect.heigth = (double)WIN_H - rect.heigth;
	rect.color = data->parsed_map->floor_color;
	cub_draw_rect(data->walls->img, &rect);
	free(coord);
}

void	cub_draw_fov(t_data *data, t_vec *from, int degrees, int len)
{
	int		deg;
	t_vec	to;
	double	radians;
	t_vec	*ray_dirvector;
	double	distance;

	deg = -(degrees / 2);
	while (deg < degrees / 2)
	{
		radians = ft_to_rad(deg);
		ray_dirvector = ft_rotate_vector_new(data->cam->dir, -radians);
		distance = cub_measure_dist_to_wall(data, ray_dirvector)
			* data->minimap->tilesize;
		if (distance == -1)
			distance = len;
		to.xd = from->xd + ray_dirvector->xd * distance;
		to.yd = from->yd + ray_dirvector->yd * distance;
		cub_drawline(data->minimap->map, from, &to, COL_FOV);
		free(ray_dirvector);
		deg += 2;
	}
}
