#include "test.h"

int	cub_handle_no_event(void *param)
{
	(void) param;
	return (EXIT_SUCCESS);
}

int	handle_stop_rotate(t_data *data, int key)
{
	if (key == K_A)
	{
		data->rotates_left = false;
	}
	else if (key == K_D)
	{
	}
	else if (key == K_W)
	{
	}
	else if (key == K_S)
	{
	}
	return (EXIT_SUCCESS);
}

int	handle_rotate(t_data *data, int key)
{
	if (key == K_A)
	{
		data->rotates_left = true;
	}
	else if (key == K_D)
	{
	}
	else if (key == K_W)
	{
	}
	else if (key == K_S)
	{
	}
	return (EXIT_SUCCESS);
}

int	cub_handle_keypress(int key, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	// printf("key pressed is %d\n", key);
	if (key == K_ESCAPE)
	{
		printf("Escape was pressed\n");
		mlx_loop_end(data->mlx->mlx);
		cub_clean_data(data);
		exit(EXIT_SUCCESS);
	}
	handle_rotate(data, key);
	return (EXIT_SUCCESS);
}

int	cub_handle_keyrelease(int key, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	handle_stop_rotate(data, key);
	// printf("key released is %d\n", key);
	return (EXIT_SUCCESS);
}
