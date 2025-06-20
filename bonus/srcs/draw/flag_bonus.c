/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:03:23 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/20 17:32:21 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static int	cub_get_flag_wave(int y, double wave_offset)
{
	int	wave_table[20] = {0, 1, 2, 2, 1, 0, -1, -2, -2, -1, 0, 1, 2, 2, 1, 0, -1, -2, -2, -1};
	int	index;
	
	index = ((int)(y + wave_offset * 3)) % 20;
	return (wave_table[index]);
}

static void	cub_draw_flag_stripe(t_data *data, t_vec *start, 
	int stripe, unsigned int color)
{
	int				x;
	int				y;
	int				wave_x;

	y = 0;
	while (y < 50)
	{
		wave_x = cub_get_flag_wave(y, data->flag_wave_offset);
		x = 0;
		while (x < 30)
		{
			cub_put_pix_to_img(data->walls->img, 
				start->x + stripe * 30 + x + wave_x, 
				start->y + y, color);
			x++;
		}
		y++;
	}
}

static void	cub_draw_flag_pole(t_data *data, t_vec *start)
{
	int	x;
	int	y;

	x = -6;
	while (x < -2)
	{
		y = -5;
		while (y < 65)
		{
			cub_put_pix_to_img(data->walls->img, start->x + x, start->y + y, 
				cub_rgb_to_int(101, 67, 33));
			y++;
		}
		x++;
	}
}

void	cub_draw_flags(t_data *data)
{
	t_vec	start;

	data->flag_frame++;
	if (data->flag_frame >= 8)
	{
		data->flag_frame = 0;
		data->flag_wave_offset += 0.2;
		if (data->flag_wave_offset > 6.28)
			data->flag_wave_offset = 0.0;
	}
start.x = WIN_W - 100;
	start.y = 20;
	cub_draw_flag_pole(data, &start);
	cub_draw_flag_stripe(data, &start, 0, FR_BLUE);
	cub_draw_flag_stripe(data, &start, 1, FR_WHITE);
	cub_draw_flag_stripe(data, &start, 2, FR_RED);
	start.x = 20;
	start.y = 20;
	cub_draw_flag_pole(data, &start);
	cub_draw_flag_stripe(data, &start, 0, ES_RED);
	cub_draw_flag_stripe(data, &start, 1, ES_YELLOW);
	cub_draw_flag_stripe(data, &start, 2, ES_RED);
}