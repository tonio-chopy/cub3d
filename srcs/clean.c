#include "test.h"

/*
 * passing 0b1001 will free index 0 and 4
 */
void	cub_clean2d(void **array, int size, unsigned int bitmask, bool freeArr)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (i < size)
	{
		if ((bitmask & (1 << i)) != 0)
			free(array[i]);
		i++;
	}
	if (freeArr)
		free(array);
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

void	cub_clean_img(t_data *data, t_img *img)
{
	if (!img)
		return ;
	if (img->location)
		free(img->location);
	mlx_destroy_image(data->mlx->mlx, img->img);
	free(img);
}

void	cub_clean_field(t_data *data, t_field *field)
{
	if (!field)
		return ;
	if (field->display)
		cub_clean_img(data, field->display);
	free(field);
}

void	cub_clean_minimap(t_data *data, t_minimap *minimap)
{
	if (!minimap)
		return ;
	if (minimap->map)
		cub_clean_img(data, minimap->map);
	if (minimap->player)
		cub_clean_img(data, minimap->player);
	free(minimap);
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

void	cub_clean_parsed(t_parsed_map *parsed)
{
	if (!parsed)
		return ;
	free(parsed->elems);
	free(parsed);
}

void	cub_clean_data(t_data *data)
{
	if (data->minimap)
		cub_clean_minimap(data, data->minimap);
	if (data->field)
		cub_clean_field(data, data->field);
	if (data->mlx)
		cub_clean_mlx(data->mlx);
	if (data->parsed_map)
		cub_clean_parsed(data->parsed_map);
	if (data->cam_vector)
		free(data->cam_vector);
	if (data->dir_vector)
		free(data->dir_vector);
	if (data->player_pos)
		free(data->player_pos);
	if (data->ray)
		cub_clean_ray(data->ray);
	free(data);
}