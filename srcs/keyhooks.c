#include "test.h"

int	handle_no_event(void *param)
{
	(void) param;
	return (EXIT_SUCCESS);
}

int	handle_keypress(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *) param;
	printf("key pressed is %d\n", key);
	if (key == K_ESCAPE)
		mlx_destroy_window(mlx->mlx, mlx->win);	
	return (EXIT_SUCCESS);
}

int	handle_keyrelease(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *) param;
	printf("key released is %d\n", key);
	if (key == 46)
		mlx_destroy_window(mlx->mlx, mlx->win);
	return (EXIT_SUCCESS);
}
