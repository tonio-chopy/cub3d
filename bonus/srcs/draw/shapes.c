/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:34:27 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/09 17:34:28 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

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

/*void	debug_data(t_data *data)
{
	if (data->debug == 'v')
		printf("Debug: player at x=%.2f, y=%.2f\n", data->player_pos->xd,
			data->player_pos->yd);
}

void	debug_ray(t_ray *ray)
{
	printf("Debug ray: hit=%d, side=%c\n", ray->has_hit, ray->side);
}

void	debug_elems(t_parsed_map *map, char *elems)
{
	int	i;

	printf("Map elements debug (%dx%d):\n", map->width, map->heigth);
	for (i = 0; i < map->nb_elems; i++)
	{
		if (i % map->width == 0 && i > 0)
			printf("\n");
		printf("%c", elems[i]);
	}
	printf("\n");
}
*/
int	cub_merge_goal_col(t_data *data, t_ray *ray, double pos, double texture_x)
{
	int	color;
	int	tex_y;
	int	tex_x;

	tex_x = (int)texture_x;
	tex_y = (int)pos;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= TEXTURE_SIZE)
		tex_x = TEXTURE_SIZE - 1;
	if (tex_y < 0)
		tex_y = 0;
	if (tex_y >= TEXTURE_SIZE)
		tex_y = TEXTURE_SIZE - 1;
	if (ray->hit_dir >= GOAL_LEFT && ray->hit_dir <= RIGHT_CATCH)
		color = data->tex[ray->hit_dir][tex_y * TEXTURE_SIZE + tex_x];
	else
		color = data->tex[ray->hit_dir][tex_y * TEXTURE_SIZE + tex_x];
	return (color);
}

// Add your bonus drawing functions here
// This file was empty in your untitled file, so I'm creating a placeholder
/*void	placeholder_bonus_shape_function(void)
{
	// Add bonus-specific drawing functions here
}
*/