/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpetit <fpetit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 13:37:09 by fpetit            #+#    #+#             */
/*   Updated: 2025/07/05 12:48:31 by fpetit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	cub_init_sound(t_data *data)
{
	int	i;
	int	fd;

	data->goal->songs[ENSEMBLE] = "sounds/ensemble.wav";
	data->goal->songs[KIKI] = "sounds/kmb.wav";
	data->goal->songs[ROJA] = "sounds/roja.wav";
	data->goal->songs[KICK] = "sounds/kick.wav";
	data->goal->songs[BOO] = "sounds/boo.wav";
	data->goal->songs[GOAL] = "sounds/goal.wav";
	i = 0;
	while (i < 6)
	{
		fd = open(data->goal->songs[i], R_OK);
		if (fd == -1)
			cub_handle_fatal(data, MSP_OPEN);
		close(fd);
		i++;
	}
}

void	try_kill_pid(int pid)
{
	int	status;

	if (kill(pid, SIGTERM) == 0)
	{
		usleep(10000);
		if (kill(pid, 0) == 0)
		{
			kill(pid, SIGKILL);
		}
	}
	while (waitpid(pid, &status, 0) < 0)
	{
		if (errno != EINTR)
			return ;
	}
}

void	cub_stop_audio(t_data *data, bool is_song)
{
	if (!data->goal->is_soccer)
		return ;
	if (!data || !data->goal)
		return ;
	if (data->goal->songpid != -1 && is_song)
	{
		try_kill_pid(data->goal->songpid);
		data->goal->songpid = -1;
		data->goal->current_song = -1;
	}
	if (data->goal->effectpid != -1 && !is_song)
	{
		try_kill_pid(data->goal->effectpid);
		data->goal->effectpid = -1;
	}
}

void	cub_play_effect(t_data *data, int index)
{
	if (!data->goal->is_soccer)
		return ;
	if (data->goal->current_song == index || index < 3)
		return ;
	cub_stop_audio(data, false);
	data->goal->effectpid = fork();
	if (data->goal->effectpid == -1)
		cub_handle_fatal(data, "Error\nfork error");
	if (data->goal->effectpid == 0)
	{
		execl("/usr/bin/paplay", "paplay", data->goal->songs[index], NULL);
		cub_clean_data(data);
		exit(EXIT_FAILURE);
	}
}

void	cub_play_song(t_data *data, int index)
{
	if (!data->goal->is_soccer || data->goal->current_song == index \
|| index >= 3)
		return ;
	cub_stop_audio(data, true);
	data->goal->current_song = index;
	data->goal->songpid = fork();
	if (data->goal->songpid == 0)
	{
		execl("/usr/bin/paplay", "paplay", data->goal->songs[index], NULL);
		cub_clean_data(data);
		exit(EXIT_FAILURE);
	}
}
