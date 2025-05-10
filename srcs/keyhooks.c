#include "test.h"

int	handle_no_event(void *param)
{
	(void) param;
	return (EXIT_SUCCESS);
}

int	handle_rotate(t_data *data, int key)
{
	if (key == K_A)
	{
		data->dir_vector->xf -= 0.1;
	}
	else if (key == K_D)
	{
		data->dir_vector->xf += 0.1;
	}
	else if (key == K_W)
	{
		data->dir_vector->yf += 0.1;
	}
	else if (key == K_S)
	{
		data->dir_vector->yf -= 0.1;
	}
	return (EXIT_SUCCESS);
}

int	handle_keypress(int key, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	// printf("key pressed is %d\n", key);
	if (key == K_ESCAPE)
	{
		mlx_loop_end(data->mlx->mlx);
		clean_data(data);
		exit(EXIT_SUCCESS);
	}
	handle_rotate(data, key);
	return (EXIT_SUCCESS);
}

int	handle_keyrelease(int key, void *param)
{
	t_mlx	*mlx;

	mlx = (t_mlx *) param;
	(void) key;
	// printf("key released is %d\n", key);
	return (EXIT_SUCCESS);
}
