/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:23:00 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/29 13:24:58 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_img	*cub_init_img_from_xpm(t_data *data, int width, int height,
		char *filename)
{
	t_img	*img;
	int		bpp;
	int		line_length;
	int		endian;

	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		return (NULL);
	img->img = mlx_xpm_file_to_image(data->mlx->mlx, filename, &width, &height);
	if (!img->img)
	{
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &bpp, &line_length, &endian);
	if (!img->addr)
	{
		cub_clean_img(data, img);
		return (NULL);
	}
	cub_update_img_info(img, bpp, line_length, endian);
	cub_update_img_coord(img, width, height, NULL);
	return (img);
}

t_img	*cub_init_img(t_data *data, int width, int height, t_vec *location)
{
	t_img	*img;
	int		bpp;
	int		line_length;
	int		endian;

	if (!location)
		cub_handle_fatal(data, "no location for img");
	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		return (NULL);
	img->img = mlx_new_image(data->mlx->mlx, width, height);
	if (!img->img)
	{
		free(img);
		return (NULL);
	}
	img->addr = mlx_get_data_addr(img->img, &bpp, &line_length, &endian);
	if (!img->addr)
	{
		cub_clean_img(data, img);
		return (NULL);
	}
	cub_update_img_info(img, bpp, line_length, endian);
	cub_update_img_coord(img, width, height, location);
	return (img);
}

void	cub_init_mlx(t_data *data)
{
	data->mlx = ft_calloc(1, sizeof(t_mlx));
	if (!data->mlx)
		cub_handle_fatal(data, MSG_ALLOC);
	data->mlx->mlx = mlx_init();
	if (!data->mlx->mlx)
		cub_handle_fatal(data, MSG_ALLOC);
	data->mlx->win = mlx_new_window(data->mlx->mlx, WIN_W, WIN_H, "Cub3D");
	if (!data->mlx->win)
		cub_handle_fatal(data, MSG_ALLOC);
}

int	cub_refresh(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	cub_update_translation(data);
	cub_update_rotation(data);
	cub_clear_img(data->walls->img);
	cub_draw_ceiling_and_floor(data);
	cub_draw_walls(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->walls->img->img, 0, 0);
	return (EXIT_SUCCESS);
}
