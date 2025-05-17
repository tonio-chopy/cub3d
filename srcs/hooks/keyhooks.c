#include "test.h"

int	cub_handle_no_event(void *param)
{
	(void) param;
	return (EXIT_SUCCESS);
}

int	handle_stop_rotate(t_data *data, int key)
{
	if (key == K_LEFT)
		data->rotates_left = false;
	else if (key == K_RIGHT)
		data->rotates_right = false;
	if (key == K_W)
		data->move_forward = false;
	else if (key == K_S)
		data->move_backward = false;
	return (EXIT_SUCCESS);
}

int	handle_rotate(t_data *data, int key)
{
	if (key == K_LEFT)
		data->rotates_left = true;
	else if (key == K_RIGHT)
		data->rotates_right = true;
	return (EXIT_SUCCESS);
}

int	handle_stop_move(t_data *data, int key)
{
	if (key == K_W)
		data->move_forward = false;
	else if (key == K_S)
		data->move_backward = false;
	if (key == K_A)
		data->move_left = false;
	else if (key == K_D)
		data->move_right = false;
	return (EXIT_SUCCESS);
}

int	handle_move(t_data *data, int key)
{
	if (key == K_W)
		data->move_forward = true;
	else if (key == K_S)
		data->move_backward = true;
	if (key == K_A)
		data->move_left = true;
	else if (key == K_D)
		data->move_right = true;
	return (EXIT_SUCCESS);
}

int	cub_handle_keypress(int key, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	// printf("key pressed is %d\n", key);
	if (key == K_ESCAPE)
	{
		mlx_loop_end(data->mlx->mlx);
		cub_clean_data(data);
		exit(EXIT_SUCCESS);
	}
	handle_rotate(data, key);
	handle_move(data, key);
	return (EXIT_SUCCESS);
}

int	cub_handle_keyrelease(int key, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	handle_stop_rotate(data, key);
	handle_stop_move(data, key);
	// printf("key released is %d\n", key);
	return (EXIT_SUCCESS);
}
