/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_img.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/01/27 11:23:00 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	cub_clean_img(t_data *data, t_img *img)
{
	if (!img)
		return ;
	if (img->location)
		free(img->location);
	mlx_destroy_image(data->mlx->mlx, img->img);
	free(img);
}

void	cub_clean_field(t_data *data, t_walls *walls)
{
	if (!walls)
		return ;
	if (walls->img)
		cub_clean_img(data, walls->img);
	free(walls);
}

void	cub_clean_ray(t_ray *ray)
{
	if (ray->current_cell)
		free(ray->current_cell);
	if (ray->step_cell)
		free(ray->step_cell);
	if (ray->delta)
		free(ray->delta);
	if (ray->side_dist)
		free(ray->side_dist);
	free(ray);
}

void	cub_clean_mlx(t_mlx *mlx)
{
	if (!mlx)
		return ;
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx_destroy_window(mlx->mlx, mlx->win);
	mlx_destroy_display(mlx->mlx);
	if (mlx->mlx)
		free(mlx->mlx);
	free(mlx);
}
