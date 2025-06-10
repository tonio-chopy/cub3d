/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 17:34:51 by alaualik          #+#    #+#             */
/*   Updated: 2025/06/10 15:37:26 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_bonus.h"

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

int	handle_mouse_rotate(int x, int y, void *param)
{
	t_data	*data;
	int		quarter_w;

	(void)y;
	data = (t_data *)param;
	quarter_w = WIN_W / 4;
	if (x < quarter_w)
		data->rotates_left = true;
	else if (x > (quarter_w * 3))
		data->rotates_right = true;
	else
	{
		data->rotates_left = false;
		data->rotates_right = false;
	}
	return (EXIT_SUCCESS);
}
