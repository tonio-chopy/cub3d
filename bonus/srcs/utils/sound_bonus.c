/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:37:09 by fpetit            #+#    #+#             */
/*   Updated: 2025/06/23 17:28:30 by alaualik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_stop_song(t_data *data, bool audio)
{
	if (data->goal->songpid != -1 && audio)
	{
		kill(data->goal->songpid, SIGTERM);
		waitpid(data->goal->songpid, NULL, 0);
		data->goal->songpid = -1;
		data->goal->current_song = -1;
	}
	if (data->goal->effectpid != -1 && !audio)
	{
		kill(data->goal->effectpid, SIGTERM);
		waitpid(data->goal->effectpid, NULL, 0);
		data->goal->effectpid = -1;
	}
}

void	cub_play_effect(t_data *data, int index)
{
	if (data->goal->current_song == index || index < 3)
		return ;
	data->goal->effectpid = fork();
	if (data->goal->effectpid == 0)
	{
		execl("/usr/bin/paplay", "paplay", data->goal->songs[index], NULL);
		exit(1);
	}
}

void	cub_play_song(t_data *data, int index)
{
	printf("asking playing song index %d\n", index);
	if (data->goal->current_song == index || index >= 3)
		return ;
	cub_stop_song(data, true);
	data->goal->current_song = index;
	data->goal->songpid = fork();
	if (data->goal->songpid == 0)
	{
		execl("/usr/bin/paplay", "paplay", data->goal->songs[index], NULL);
		exit(1);
	}
}
