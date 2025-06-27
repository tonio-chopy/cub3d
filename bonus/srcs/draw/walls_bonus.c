/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:34:30 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/27 19:34:19 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

/*
 * centers vertically
 * reduces value if overflows viewport bottom or top
 */
void	adjust_y_for_viewport(t_data *data, double pro_height, t_vec *bottom, \
t_vec *top)
{
	int	vertical_center;

	vertical_center = WIN_H * data->walls->ceiling_ratio;
	top->yd = vertical_center + pro_height / 2;
	bottom->yd = vertical_center - pro_height / 2;
	if (bottom->yd < 0)
		bottom->yd = 0;
	if (top->yd > WIN_H)
		top->yd = (double) WIN_H - 1;
}

void	cub_adjust_dir_for_goals(t_data *data, t_ray *ray)
{
	char	elem;

	// printf("current cell x %d y %d\n", ray->current_cell->x,
	// ray->current_cell->y);
	elem = data->parsed_map->elems[(int) ray->current_cell->yd \
* data->parsed_map->width + (int) ray->current_cell->xd];
	if (elem == E_GOAL_LEFT)
		ray->hit_dir = GOAL_LEFT;
	else if (elem == E_GOAL_CENTER)
		ray->hit_dir = GOAL_CENTER;
	else if (elem == E_GOAL_RIGHT)
		ray->hit_dir = GOAL_RIGHT;
}

/*
 * viewport_x is the current x where we cast a ray
 * projected height = wall height * projected dist / wall dist
 * start painting from other extremity when raydir doesnt match the x or y axis
 */
void	cub_drawline_wall(t_data *data, double dist, t_ray *ray, \
int viewport_x)
{
	t_vec	bottom;
	t_vec	top;

	if (dist < 0.0001)
		dist = 0.0001;
	ray->pro_height = WIN_H / dist;
	ray->hit_dir = get_direction(ray->side, ray->raydir);
	cub_adjust_dir_for_goals(data, ray);
	bottom.xd = viewport_x;
	top.xd = viewport_x;
	adjust_y_for_viewport(data, ray->pro_height, &bottom, &top);
	cub_apply_texture(data, &bottom, top.yd, ray);
}

void	cub_draw_wall_for_x(t_data *data, int x, double degrees, \
t_vec *ray_dirvector)
{
	double	distance;
	double	distorsion_corrector;

	distorsion_corrector = cosf(ft_to_rad(degrees));
	distance = cub_measure_dist_to_wall(data, ray_dirvector) * \
distorsion_corrector;
	data->zbuffer[x] = distance;
	cub_drawline_wall(data, distance, data->ray, x);
}

void	cub_draw_walls(t_data *data)
{
	int		x;
	double	inc_degrees;
	double	degrees;
	t_vec	*ray_dirvector;
	double	cam_x_vector;

	x = 0;
	degrees = -(FOV_DEGREES / 2);
	inc_degrees = FOV_DEGREES / (double) WIN_W;
	data->goal->can_see_goal = false;
	while (x < WIN_W)
	{
		cam_x_vector = x * 2 / (double) WIN_W - 1.0;
		degrees += inc_degrees;
		ray_dirvector = ft_rotate_vector_new(data->cam->dir, \
ft_to_rad(degrees));
		cub_draw_wall_for_x(data, x, degrees, ray_dirvector);
		x++;
		free(ray_dirvector);
	}
}
