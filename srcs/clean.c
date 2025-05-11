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

void	cub_clean_mlx_and_img(t_mlx *mlx, t_img *main_img)
{
	mlx_destroy_image(mlx->mlx, main_img->addr);
	mlx_destroy_display(mlx->mlx);
	mlx_destroy_window(mlx->mlx, mlx->win);
	free(mlx->mlx);
	free(mlx);
	free(main_img);
}

void	clean_img(t_data *data, t_img *img)
{
	if (!img)
		return ;
	if (img->location)
		free(img->location);
	mlx_destroy_image(data->mlx->mlx, img->img);
	free(img);
}

void	clean_minimap(t_data *data, t_minimap *minimap)
{
	if (!minimap)
		return ;
	if (minimap->map)
		clean_img(data, minimap->map);
	if (minimap->player)
		clean_img(data, minimap->player);
	free(minimap);
}

void	clean_mlx(t_mlx *mlx)
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

void	clean_parsed(t_parsed_map *parsed)
{
	if (!parsed)
		return ;
	free(parsed->elems);
	free(parsed);
}

void	cub_clean_data(t_data *data)
{
	if (data->minimap)
		clean_minimap(data, data->minimap);
	if (data->mlx)
		clean_mlx(data->mlx);
	if (data->parsed_map)
		clean_parsed(data->parsed_map);
	free(data->player_pos);
	free(data);
}