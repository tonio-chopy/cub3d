/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_img_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:36:01 by alaualik          #+#    #+#             */
/*   Updated: 2025/07/03 21:02:21 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_clean_img(t_data *data, t_img *img)
{
	if (!img)
		return ;
	if (img->location)
		free(img->location);
	if (img->img && data && data->mlx && data->mlx->mlx)
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
	if (!ray)
		return ;
	if (ray->current_cell)
		free(ray->current_cell);
	if (ray->step_cell)
		free(ray->step_cell);
	if (ray->delta)
		free(ray->delta);
	if (ray->side_dist)
		free(ray->side_dist);
	if (ray->check_cell)
		free(ray->check_cell);
	free(ray);
}

void	cub_clean_mlx(t_mlx *mlx)
{
	if (!mlx)
		return ;
	if (mlx->win && mlx->mlx)
		mlx_clear_window(mlx->mlx, mlx->win);
	if (mlx->win && mlx->mlx)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->mlx)
	{
		mlx_destroy_display(mlx->mlx);
		free(mlx->mlx);
	}
	free(mlx);
}

void	cub_clean_balls(t_data *data)
{
	int	i;

	if (!data->balls)
		return ;
	i = 0;
	while (i < data->nb_ball)
	{
		free(data->balls[i]->pos);
		free(data->balls[i]);
		i++;
	}
	free(data->balls);
}
