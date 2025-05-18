#include "test.h"

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
