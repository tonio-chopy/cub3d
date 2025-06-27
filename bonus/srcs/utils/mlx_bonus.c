/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaualik <alaualik@42angouleme.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 21:15:14 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/27 21:17:11 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

t_img	*cub_init_img_from_xpm(t_data *data, int width, int height, \
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
