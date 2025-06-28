/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 16:03:23 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/28 16:46:08 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

static void	cub_init_wave_table(int *wt)
{
	wt[0] = 0;
	wt[1] = 1;
	wt[2] = 2;
	wt[3] = 2;
	wt[4] = 1;
	wt[5] = 0;
	wt[6] = -1;
	wt[7] = -2;
	wt[8] = -2;
	wt[9] = -1;
	wt[10] = 0;
	wt[11] = 1;
	wt[12] = 2;
	wt[13] = 2;
	wt[14] = 1;
	wt[15] = 0;
	wt[16] = -1;
	wt[17] = -2;
	wt[18] = -2;
	wt[19] = -1;
}

static int	cub_get_flag_wave(int y, double wave_offset)
{
	int	wt[20];
	int	index;

	cub_init_wave_table(wt);
	index = ((int)(y + wave_offset * 3)) % 20;
	return (wt[index]);
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
				start->xd + stripe * 30 + x + wave_x,
				start->yd + y, color);
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
			cub_put_pix_to_img(data->walls->img, start->xd + x, start->yd + y,
				cub_rgb_to_int(101, 67, 33));
			y++;
		}
		x++;
	}
}

void	cub_draw_flags(t_data *data)
{
	t_vec	start;

	if (!data->goal->is_soccer)
		return ;
	data->flag_frame++;
	if (data->flag_frame >= 8)
	{
		data->flag_frame = 0;
		data->flag_wave_offset += 0.2;
		if (data->flag_wave_offset > 6.28)
			data->flag_wave_offset = 0.0;
	}
	start.xd = WIN_W - 100;
	start.yd = 20;
	cub_draw_flag_pole(data, &start);
	cub_draw_flag_stripe(data, &start, 0, FR_BLUE);
	cub_draw_flag_stripe(data, &start, 1, FR_WHITE);
	cub_draw_flag_stripe(data, &start, 2, FR_RED);
	start.xd = 20;
	start.yd = 20;
	cub_draw_flag_pole(data, &start);
	cub_draw_flag_stripe(data, &start, 0, ES_RED);
	cub_draw_flag_stripe(data, &start, 1, ES_YELLOW);
	cub_draw_flag_stripe(data, &start, 2, ES_RED);
}
