/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:36:15 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/23 17:30:23 by alaualik         ###   ########.fr       */
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

t_img	*cub_init_img(t_data *data, int width, int height, t_vec *location)
{
	t_img	*img;
	int		bpp;
	int		line_length;
	int		endian;

	if (!location)
		cub_handle_fatal(data, "no location for img\n");
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

t_mlx	*cub_init_mlx( void )
{
	t_mlx	*mlx;
	void	*mlxptr;
	void	*mlxwin;

	mlx = ft_calloc(1, sizeof(t_mlx));
	if (!mlx)
		return (NULL);
	mlxptr = mlx_init();
	if (!mlxptr)
	{
		free(mlx);
		return (NULL);
	}
	mlx->mlx = mlxptr;
	mlxwin = mlx_new_window(mlx->mlx, WIN_W, WIN_H, "Test");
	if (!mlxwin)
	{
		free(mlx);
		return (NULL);
	}
	mlx->win = mlxwin;
	return (mlx);
}

void	cub_update_score(t_data *data)
{
	int		i;
	t_img	*score;

	if (data->goal->shootcount == 0)
		return ;
	i = 0;
	while (i < data->goal->shootcount)
	{
		score = data->goal->ko;
		if (data->goal->results[i] == true)
			score = data->goal->ok;
		cub_cpy_with_transparency(data->walls->img, score, 150 + i * 100, 10);
		i++;
	}
}

int	cub_refresh(void *param)
{
	t_data	*data;

	data = (t_data *) param;
	cub_update_goal_anim(data);
	cub_update_translation(data);
	cub_update_rotation(data);
	cub_clear_img(data->minimap->map);
	cub_clear_img(data->walls->img);
	cub_draw_ceiling_and_floor(data);
	cub_draw_walls(data);
	cub_draw_ball(data);
	cub_draw_minimap(data);
	cub_draw_flags(data);
	cub_draw_player(data);
	cub_cpy_with_transparency(data->walls->img, data->minimap->map,
		data->minimap->map->location->x, data->minimap->map->location->y);
	cub_update_score(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, \
data->walls->img->img, 0, 0);
	if (data->show_help)
		cub_draw_help(data);
	return (EXIT_SUCCESS);
}
