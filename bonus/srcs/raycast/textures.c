/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:35:50 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/14 11:51:25 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_bonus.h"

void	do_copy_2d(int *tab, t_img *img, int *img_data)
{
	int		x;
	int		y;
	t_vec	scale;
	int		x_src;
	int		y_src;

	scale.yd = (double) img->height / TEXTURE_SIZE;
	scale.xd = (double) img->width / TEXTURE_SIZE;
	y = 0;
	while (y < TEXTURE_SIZE)
	{
		x = 0;
		while (x < TEXTURE_SIZE)
		{
			x_src = x * scale.xd;
			y_src = y * scale.yd;
			tab[(int)(y * TEXTURE_SIZE + x)] \
= img_data[(int)(y_src * img->line_length / 4 + x_src)];
			x++;
		}
		y++;
	}
}

void	copy_texture(t_img *img, int *tab)
{
	int		bpp;
	int		line_length;
	int		endian;
	int		*img_data;

	img_data = (int *)mlx_get_data_addr(img->img, &bpp, &line_length, &endian);
	if (bpp != 32)
	{
		ft_puterr("texture format not supported\n");
		return ;
	}
	img->line_length = line_length;
	img->endian = endian;
	do_copy_2d(tab, img, img_data);
}

int	*cub_read_texture(t_data *data, char *file)
{
	int		*tab;
	void	*img_ptr;
	int		img_w;
	int		img_h;
	t_img	img;

	tab = ft_calloc(TEXTURE_SIZE * TEXTURE_SIZE, sizeof(int));
	if (!tab)
		cub_handle_fatal(data, "error init texture tab\n");
	img_ptr = mlx_xpm_file_to_image(data->mlx->mlx, file, &img_w, &img_h);
	if (!img_ptr)
	{
		free(tab);
		cub_handle_fatal(data, "error creating texture img\n");
	}
	img.img = img_ptr;
	img.width = img_w;
	img.height = img_h;
	copy_texture(&img, tab);
	mlx_destroy_image(data->mlx->mlx, img_ptr);
	return (tab);
}

void	cub_apply_texture(t_data *data, t_vec *from, double toY, t_ray *ray)
{
	double			step;
	double			pos;
	unsigned int	color;
	double			y;
	double			texture_x;

	texture_x = (int)(ray->wall_ratio * TEXTURE_SIZE);
	if ((ray->side == 'x' && ray->raydir->xd < 0) || (ray->side == 'y' \
&& ray->raydir->yd > 0))
		texture_x = TEXTURE_SIZE - texture_x - 1;
	y = from->yd;
	step = (double) TEXTURE_SIZE / ray->pro_height;
	pos = (y - WIN_H / 2 + ray->pro_height / 2) * step;
	while (y < toY)
	{
		color = cub_merge_goal_col(data, ray, pos, texture_x);
		pos += step;
		if (ray->hit_dir == NORTH || ray->hit_dir == SOUTH)
			color = (color >> 1) & 0x7F7F7F;
		cub_put_pix_to_img(data->walls->img, (int) from->xd, (int) y, color);
		y++;
	}
}
