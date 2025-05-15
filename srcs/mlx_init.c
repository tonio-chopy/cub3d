#include "test.h"

static void	cub_update_img_info(t_img *img, int bpp, int line_length, int endian)
{
	img->bpp = bpp;
	img->line_length = line_length;
	img->endian = endian;
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
		mlx_destroy_image(data->mlx->mlx, img->img);
		free(img);
		return (NULL);
	}
	cub_update_img_info(img, bpp, line_length, endian);
	img->width = width;
	img->height = height;
	img->location = location;
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

void	cub_clear_img(t_img *img)
{
	int	y;
	int	x;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			cub_put_pix_to_img(img, x, y, BLACK);
			x++;
		}
		y++;
	}
}

static void	cub_update_rotation(t_data *data)
{
	if (data->rotates_left)
	{
		ft_rotate_vector(data->cam->dir, -(ROTATION_SPEED / 5));
		ft_rotate_vector(data->cam->plane, -(ROTATION_SPEED / 5));
	}
	else if (data->rotates_right)
	{
		ft_rotate_vector(data->cam->dir, (ROTATION_SPEED / 5));
		ft_rotate_vector(data->cam->plane, (ROTATION_SPEED / 5));
	}
}

void	cub_update_translation(t_data *data)
{
	t_vec target;
	t_vec	move_vector;

	target.xd = data->player_pos->xd;
	target.yd = data->player_pos->yd;
	move_vector.xd = 0;
	move_vector.yd = 0;
	if (data->move_forward)
	{
		move_vector.xd += (data->cam->dir->xd * MOVEMENT_SPEED);
		move_vector.yd += (data->cam->dir->yd * MOVEMENT_SPEED);
	}
	else if (data->move_backward)
	{
		move_vector.xd -= (data->cam->dir->xd * MOVEMENT_SPEED);
		move_vector.yd -= (data->cam->dir->yd * MOVEMENT_SPEED);
	}
	if (data->move_left)
	{
		move_vector.xd += (data->cam->dir->yd * MOVEMENT_SPEED);
		move_vector.yd += (-data->cam->dir->xd * MOVEMENT_SPEED);	
	}
	else if (data->move_right)
	{
		move_vector.xd += (-data->cam->dir->yd * MOVEMENT_SPEED);
		move_vector.yd += (data->cam->dir->xd * MOVEMENT_SPEED);
	}
	target.xd += move_vector.xd;
	target.yd += move_vector.yd;
	move_if_possible(data, &target, &move_vector);
}

int cub_refresh(void *param)
{
	t_data	*data;

	data = (t_data *) param;
	cub_update_translation(data);
	cub_update_rotation(data);
	cub_clear_img(data->minimap->map);
	cub_clear_img(data->field->display);
	cub_draw_walls(data);
	cub_draw_minimap(data);
	cub_draw_player(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->field->display->img, 0, 0);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win, data->minimap->map->img, data->minimap->map->location->x, data->minimap->map->location->y);
	return (EXIT_SUCCESS);
}