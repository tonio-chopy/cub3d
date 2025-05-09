#include "test.h"

/*
 * passing 0b1001 will free index 0 and 4
 */
void	clean2d(void **array, int size, unsigned int bitmask, bool freeArr)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (i < size)
	{
		if (bitmask & (1 << i) != 0)
			free(array[i]);
		i++;
	}
	if (freeArr)
		free(array);
}

void	clean_mlx_and_img(t_mlx *mlx, t_img *main_img)
{
	mlx_destroy_image(mlx->mlx, main_img->addr);
	mlx_destroy_display(mlx->mlx);
	mlx_destroy_window(mlx->mlx, mlx->win);
	free(mlx->mlx);
	free(mlx);
	free(main_img);
}
