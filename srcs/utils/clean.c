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

void	cub_clean_field(t_data *data, t_walls *walls)
{
	if (!walls)
		return ;
	if (walls->img)
		cub_clean_img(data, walls->img);
	free(walls);
}

void	cub_clean_minimap(t_data *data, t_minimap *minimap)
{
	if (!minimap)
		return ;
	if (minimap->map)
		cub_clean_img(data, minimap->map);
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

void	cub_clean_cam(t_cam *cam)
{
	if (cam->dir)
		free(cam->dir);
	if (cam->plane)
		free(cam->plane);
	free(cam);
}

void	cub_clean_text(int **tab)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	cub_clean_data(t_data *data)
{
	if (data->minimap)
		cub_clean_minimap(data, data->minimap);
	if (data->walls)
		cub_clean_field(data, data->walls);
	if (data->mlx)
		cub_clean_mlx(data->mlx);
	if (data->parsed_map)
		cub_clean_parsed(data->parsed_map);
	if (data->cam)
		cub_clean_cam(data->cam);
	if (data->player_pos)
		free(data->player_pos);
	if (data->ray)
		cub_clean_ray(data->ray);
	if (data->tex)
		cub_clean_text(data->tex);
	free(data);
}