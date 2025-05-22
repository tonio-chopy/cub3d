#include "shoot_bonus.h"

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
	if (key == K_ESCAPE)
	{
		mlx_loop_end(data->mlx->mlx);
		cub_clean_data(data);
		exit(EXIT_SUCCESS);
	}
	handle_rotate(data, key);
	handle_move(data, key);
	handle_shoot(data, key);
	return (EXIT_SUCCESS);
}

int	cub_handle_keyrelease(int key, void *param)
{
	t_data	*data;

	data = (t_data *) param;
	handle_stop_rotate(data, key);
	handle_stop_move(data, key);
	return (EXIT_SUCCESS);
}

int	handle_click_on_close(void *param)
{
	t_data *data;

	data = (t_data *) param;
	mlx_loop_end(data->mlx->mlx);
	cub_clean_data(data);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}